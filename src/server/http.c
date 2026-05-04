/* http.c */
#include <netinet/in.h>
#include <pthread.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <server/executor.h>
#include <server/http.h>
#include <server/parser.h>
#include <server/route.h>
#include <server/server.h>
#include <structs/dict/dict.h>


const char *ERR_500_RESPONSE = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 21\r\nConnection: close\r\n\r\nInternal Server Error";

typedef struct _client { // access modifier kind of thing
	int client;
	http *server;
} _client;

http *http_construct(unsigned short port, size_t thread_cnt) {
	http *http_server = malloc(sizeof(http));

	if (!http_server) {
		fprintf(stderr, "[ERROR]: %s :: malloc failed for http server struct\n", __func__);
		return NULL;
	}

	http_server->port = port;
	http_server->thread_cnt = thread_cnt;
	http_server->srv = server_construct(AF_INET, SOCK_STREAM, 0, port, 255, INADDR_ANY);

	http_server->routes = dict_construct();
	strcpy(http_server->static_dir, "frontend"); // "frontend" itself is just a temp val
	http_server->launch = launch;

	fprintf(stdout, "[SUCCESS]: %s :: http server constructed on port %d\n", __func__, port);
	return http_server;
}

void register_route(http *srv, char *(*route_func)(http *srv, request *req),
		char *uri, int count_methods, ...) {

	if (!srv || !route_func || !uri) {
		fprintf(stderr, "[ERROR]: %s :: null srv, route_func, or uri\n", __func__);
		return;
	}

	route *rte = route_construct();

	va_list methods;
	va_start(methods, count_methods);
	for (int i = 0; i < count_methods; i++) {
		rte->methods[i] = va_arg(methods, int); // storing methods in ->methods[i]
	}
	rte->route_func = route_func;
	va_end(methods);

	dict_insert(srv->routes, uri, rte, sizeof(route));

	fprintf(stdout, "[SUCCESS]: %s :: route registered for uri '%s'\n", __func__, uri);
}

void register_static_dir(http *srv, const char *dir_path) {
	if (!srv || !dir_path) {
		fprintf(stderr, "[ERROR]: %s :: null srv or dir_path\n", __func__);
		return;
	}
	strncpy(srv->static_dir, dir_path, 255);
	srv->static_dir[255] = '\0';
	fprintf(stdout, "[DEBUG]: %s :: static directory set to '%s'\n", __func__, dir_path);
}

void launch(struct http *http_server) {
	if (!http_server) {
		fprintf(stderr, "[ERROR]: %s :: null http server pointer\n", __func__);
		return;
	}
	executor *exec = exec_create(http_server->thread_cnt);
	if (!exec)
		return;

	struct sockaddr *address =
		(struct sockaddr *)&(http_server->srv->address);

	if (!address)
		return;
	socklen_t address_length = sizeof(http_server->srv->address);

	fprintf(stdout, "[MISC]: %s :: listening — http://127.0.0.1:%d\n", __func__, http_server->port);

	while (1) {
		_client *cnt = malloc(sizeof(_client));
		if (!cnt) {
			fprintf(stderr, "[ERROR]: %s :: malloc failed for client struct\n", __func__);
			continue;
		}

		cnt->client = (int)accept(http_server->srv->socket, address, &address_length);
		cnt->server = http_server;

		exec_add_work(exec, handler, cnt);
	}
}

char *render_func(const char *status, int file_count, ...) {
	if (file_count <= 0) {
		fprintf(stderr, "[ERROR]: %s :: file_count must be greater than zero\n", __func__);
		return NULL;
	}

	va_list args;
	va_start(args, file_count);

	size_t total_size = 0;
	char **buffers = malloc(sizeof(char *) * (size_t)file_count);
	size_t *sizes = malloc(sizeof(size_t) * (size_t)file_count);

	if (!buffers || !sizes) {
		if (buffers)
			free(buffers);
		if (sizes)
			free(sizes);
		va_end(args);
		return NULL;
	}

	for (int i = 0; i < file_count; i++) {
		char *path = va_arg(args, char *);
		FILE *fp = fopen(path, "r");
		if (!fp) {
			fprintf(stderr, "[ERROR]: %s :: failed to open file '%s'\n", __func__, path);
			buffers[i] = NULL;
			sizes[i] = 0;
			continue;
		}
		fseek(fp, 0, SEEK_END);
		sizes[i] = (size_t)ftell(fp);
		fseek(fp, 0, SEEK_SET);

		buffers[i] = malloc(sizes[i] + 1);
		if (buffers[i]) {
			size_t read_sz = fread(buffers[i], 1, sizes[i], fp);
			buffers[i][read_sz] = '\0';
			total_size += read_sz;
		}
		fclose(fp);
	}
	va_end(args);

	char *response = malloc(total_size + 1024);
	if (!response) {
		for (int i = 0; i < file_count; i++)
			if (buffers[i])
				free(buffers[i]);
		free(buffers);
		free(sizes);
		return NULL;
	}

	char *body_ptr = malloc(total_size + 1);
	if (!body_ptr) {
		free(response);
		for (int i = 0; i < file_count; i++)
			if (buffers[i])
				free(buffers[i]);
		free(buffers);
		free(sizes);
		return NULL;
	}

	size_t offset = 0;
	for (int i = 0; i < file_count; i++) {
		if (buffers[i]) {
			memcpy(body_ptr + offset, buffers[i], sizes[i]);
			offset += sizes[i];
			free(buffers[i]);
		}
	}
	body_ptr[offset] = '\0';
	free(buffers);
	free(sizes);

	sprintf(response,
			"HTTP/1.1 %s\r\n"
			"Content-Type: text/html; charset=UTF-8\r\n"
			"Content-Length: %zu\r\n"
			"Connection: keep-alive\r\n"
			"\r\n"
			"%s",
			status ? status : "200 OK", total_size, body_ptr);
	free(body_ptr);
	return response;
}

void handler(void *arg) {
	if (!arg) {
		fprintf(stderr, "[ERROR]: %s :: handler received null argument\n", __func__);
		return;
	}

	_client cnt = *(_client *)arg;
	free(arg);
	int keep_alive = 1;

	while (keep_alive) {
		size_t MAX_BUFFER = 8192; // 8 KB limit
		char *reqstr = malloc(MAX_BUFFER);
		if (!reqstr) {
			fprintf(stderr, "[ERROR]: %s :: malloc failed for request buffer\n", __func__);
			break;
		}

		size_t bytes_read =
			(size_t)read(cnt.client, reqstr, MAX_BUFFER - 1);
		if (bytes_read <= 0) {
			free(reqstr);
			break;
		}
		reqstr[bytes_read] = '\0';

		request *req = request_construct(reqstr);
		free(reqstr); // req string is safely copied inside parser

		if (req && req->headers) {
			char *conn_hdr =
				(char *)dict_search(req->headers, "Connection");
			if (conn_hdr && (strcmp(conn_hdr, "close") == 0 ||
						strcmp(conn_hdr, "Close") == 0)) {
				keep_alive = 0;
			}
		}

		char *uri = (char *)dict_search(req->req_line, "uri");

		route *rte = (route *)dict_search(cnt.server->routes, uri);

		if (!rte) {
			char *response = NULL;
			if (uri) {
				char filepath[512];
				if (strcmp(uri, "/") == 0) {
					snprintf(filepath, sizeof(filepath),
							"%s/index.html",
							cnt.server->static_dir);
				} else {
					snprintf(filepath, sizeof(filepath),
							"%s%s", cnt.server->static_dir,
							uri);
				}

				if (access(filepath, F_OK) != -1) {
					response = render_func("200 OK", 1, filepath);
				}
			}

			if (!response) {
				char error_path[512];
				snprintf(error_path, sizeof(error_path), "%s/error.html", cnt.server->static_dir);
				response = render_func("404 Not Found", 1, error_path);
			}

			if (response) {
				if (write(cnt.client, response, strlen(response)) < 0) {
					fprintf(stderr, "[ERROR]: %s :: failed to write static fallback response\n", __func__);
				}
				free(response);
			}

			request_destruct(req);
			if (!keep_alive)
				break;
			continue;
		}

		char *response = rte->route_func(cnt.server, req);

		if (!response) {
			char filepath[512];
			snprintf(filepath, sizeof(filepath), "%s/index.html", cnt.server->static_dir);
			FILE *fp = fopen(filepath, "r");
			if (!fp) {
				fprintf(stderr, "[ERROR]: %s :: route returned null, failed to open fallback index.html\n", __func__);
				if (write(cnt.client, ERR_500_RESPONSE,
							strlen(ERR_500_RESPONSE)) < 0) {
				}
				request_destruct(req);
				break;
			}

			fseek(fp, 0, SEEK_END);
			size_t file_size = (size_t)ftell(fp);
			fseek(fp, 0, SEEK_SET);

			char *file_buf = malloc(file_size + 1);
			if (!file_buf) {
				fprintf(stderr, "[ERROR]: %s :: malloc failed for file buffer\n", __func__);
				fclose(fp);
				if (write(cnt.client, ERR_500_RESPONSE,
							strlen(ERR_500_RESPONSE)) < 0) {
				}
				request_destruct(req);
				break;
			}

			size_t read_sz = fread(file_buf, 1, file_size, fp);
			if (read_sz != file_size) {
				fprintf(stderr, "[ERROR]: %s :: partial file read (%zu of %zu bytes)\n", __func__, read_sz, file_size);
			}
			file_buf[file_size] = '\0';
			fclose(fp);

			response = malloc(file_size + 1024);
			if (!response) {
				fprintf(stderr, "[ERROR]: %s :: malloc failed for " "response buffer\n", __func__);
				free(file_buf);
				if (write(cnt.client, ERR_500_RESPONSE, strlen(ERR_500_RESPONSE)) < 0) {
				}
				request_destruct(req);
				break;
			}

			sprintf(response, 
					"HTTP/1.1 200 OK\r\n"
					"Content-Type: text/html; charset=UTF-8\r\n"
					"Content-Length: %zu\r\n"
					"Connection: %s\r\n"
					"\r\n"
					"%s",
					file_size, keep_alive ? "keep-alive" : "close",
					file_buf);

			free(file_buf);
		}

		if (write(cnt.client, response, strlen(response)) < 0) {
			fprintf(stderr, "[ERROR]: %s :: failed to write response to client\n", __func__);
			keep_alive = 0;
		}

		if (response)
			free(response);
		request_destruct(req);
	}
	close(cnt.client);
}
