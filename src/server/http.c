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

#include <server/http.h>
#include <server/parser.h>
#include <server/route.h>
#include <server/server.h>
#include <server/executor.h>
#include <structs/dict/dict.h>

#define THREAD_CNT 10

// access modifier kind of thing

typedef struct _client{
	int client;
	http *server;
} _client;

http *http_construct(void) {
	http *http_server = malloc(sizeof(http));

	if (!http_server) {
		fprintf(stdout, "[%s]: error malloc failed http.c\n", __func__);
		return NULL;
	}

	http_server->srv = server_construct(AF_INET, SOCK_STREAM, 0, 1028, 255, INADDR_ANY);

	http_server->routes = dict_construct();
	http_server->launch = launch;

	fprintf(stdout, "[%s]: debug http server constructed http.c\n", __func__);
	return http_server;
}


void register_route(http *srv, char *(*route_func)(http *srv, request *req),
		char *uri, int count_methods, ...) {

	if (!srv)
		return;

	route *rte = route_construct();

	va_list methods;
	va_start(methods, count_methods);
	for (int i = 0; i < count_methods; i++) {
		rte->methods[i] = va_arg(methods, int); // storing methods in ->methods[i]
	}
	strcpy(rte->uri, uri);
	rte->route_func = route_func;
	va_end(methods);

	dict_insert(srv->routes, uri, rte, sizeof(route));

	fprintf(stdout, "[%s]: debug route registered for uri '%s' http.c\n", __func__, uri);
}


void handler(void *arg) {
	if (!arg) return;

	_client cnt = *(_client *)arg;
	free(arg);
	size_t MAX_BUFFER = 16 * 1024 * 1024; // 16 MB limit
	char *reqstr = malloc(MAX_BUFFER);
	if (!reqstr) {
		fprintf(stdout, "[%s]: error failed to allocate request buffer http.c\n", __func__);
		close(cnt.client);
		return;
	}


	ssize_t bytes_read = read(cnt.client, reqstr, MAX_BUFFER - 1);
	if (bytes_read <= 0) {
		free(reqstr);
		close(cnt.client);
		return;
	}
	reqstr[bytes_read] = '\0';



	request *req = request_construct(reqstr);
	free(reqstr); // req string is safely copied inside parser


	char *uri = (char *)dict_search(req->req_line, "uri");


	route *rte = (route *)dict_search(cnt.server->routes, uri);


	if (!rte) {
		char *response;
		if (uri && strcmp(uri, "/") == 0) {
			response = render_func("200 OK", 1, "files/index.html");
		} else {
			response = render_func("404 Not Found", 1, "files/error.html");
		}

		if (response) {
			if (write(cnt.client, response, strlen(response)) < 0) {
				fprintf(stdout, "[%s]: error failed to write fallback response http.c\n", __func__);
			}
			free(response);
		}

		request_destruct(req);
		close(cnt.client);
		return;
	}

	char* response = rte->route_func(cnt.server, req);

	if (!response) {
		FILE *fp = fopen("files/index.html", "r");
		if (!fp) {
			fprintf(stdout, "[%s]: error failed to open index.html http.c\n", __func__);
			exit(1);
		}

		fseek(fp, 0, SEEK_END);
		size_t file_size = (size_t)ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char *file_buf = malloc(file_size + 1);
		if (!file_buf) {
			fprintf(stdout, "[%s]: error malloc failed http.c\n", __func__);
			fclose(fp);
			exit(1);
		}

		size_t read_sz = fread(file_buf, 1, file_size, fp);
		if (read_sz != file_size) {
			fprintf(stdout, "[%s]: error failed to read complete file http.c\n", __func__);
		}
		file_buf[file_size] = '\0';
		fclose(fp);

		response = malloc(file_size + 1024);
		if (!response) {
			fprintf(stdout, "[%s]: error malloc failed for response http.c\n", __func__);
			free(file_buf);
			exit(1);
		}

		sprintf(response,
				"HTTP/1.1 200 OK\r\n"
				"Content-Type: text/html; charset=UTF-8\r\n"
				"Content-Length: %ld\r\n"
				"Connection: close\r\n"
				"\r\n"
				"%s",
				file_size, file_buf);

		free(file_buf);

	}


	if (write(cnt.client, response, strlen(response)) < 0) {
		fprintf(stdout, "[%s]: error failed to write response http.c\n", __func__);
	}


	request_destruct(req);
	close(cnt.client);
}

void launch(struct http *http_server) {
	if (!http_server) return;
	executor *exec = exec_create(THREAD_CNT);
	if (!exec) return;

	struct sockaddr *address = (struct sockaddr *)&(http_server->srv->address);

	if (!address) return;
	socklen_t address_length = sizeof(http_server->srv->address);

	while (1) {
		_client *cnt = malloc(sizeof(_client));


		cnt->client = (int)accept(http_server->srv->socket, address, &address_length);

		cnt->server = http_server;


		if (exec_add_work(exec, handler, cnt)) {

		}

	}

}

char* render_func(const char *status, int file_count, ...) {
	if (file_count <= 0) return NULL;

	va_list args;
	va_start(args, file_count);

	size_t total_size = 0;
	char **buffers = malloc(sizeof(char*) * (size_t)file_count);
	size_t *sizes = malloc(sizeof(size_t) * (size_t)file_count);

	if (!buffers || !sizes) {
		if (buffers) free(buffers);
		if (sizes) free(sizes);
		va_end(args);
		return NULL;
	}

	for (int i = 0; i < file_count; i++) {
		char *path = va_arg(args, char*);
		FILE *fp = fopen(path, "r");
		if (!fp) {
			fprintf(stdout, "[%s]: error failed to open %s http.c\n", __func__, path);
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
		for (int i = 0; i < file_count; i++) if (buffers[i]) free(buffers[i]);
		free(buffers);
		free(sizes);
		return NULL;
	}

	char *body_ptr = malloc(total_size + 1);
	if (!body_ptr) {
		free(response);
		for (int i = 0; i < file_count; i++) if (buffers[i]) free(buffers[i]);
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
			"Connection: close\r\n"
			"\r\n"
			"%s",
			status ? status : "200 OK",
			total_size, body_ptr);
	free(body_ptr);
	return response;
}

