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

#define THREAD_CNT 2

// access modifier kind of thing

typedef struct _client{
	int client;
	http *server;
} _client;

http *http_construct(void) {
	http *http_server = malloc(sizeof(http));

	if (!http_server) {
		fprintf(stderr, "error: [%s]: malloc failed\n", __func__);
		return NULL;
	}

	http_server->srv = server_construct(AF_INET, SOCK_STREAM, 0, 1028, 255, INADDR_ANY);

	http_server->routes = dict_construct();
	http_server->launch = launch;

	fprintf(stderr, "debug: [%s]: http server constructed\n", __func__);
	return http_server;
}

char *fetch_page(void) { return "[success]: fetch-page"; }

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

	fprintf(stderr, "debug: [%s]: route registered for uri '%s'\n", __func__, uri);
}

void serve_fallback(int client_sock, const char *uri) {
	char *filepath = NULL;
	char *content_type = "text/html";
	int is_404 = 0;

	if (uri && strcmp(uri, "/assets/404.webp") == 0) {
		filepath = "files/assets/404.webp";
		content_type = "image/webp";
	} else if (uri && strcmp(uri, "/") == 0) {
		filepath = "files/index.html";
	} else {
		filepath = "files/error.html";
		is_404 = 1;
	}

	FILE *fp = fopen(filepath, "rb");
	if (!fp) {
		char *not_found = "HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\n404 Route Not Found";
		if (!write(client_sock, not_found, strlen(not_found))) {
			// err msg
		}
		return;
	}

	fseek(fp, 0, SEEK_END);
	size_t file_size = (size_t)ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *file_buf = malloc(file_size);
	if (!file_buf) {
		fclose(fp);
		return;
	}

	size_t read_sz = fread(file_buf, 1, file_size, fp);
	if (!read_sz) {
		// errmsg
	}
	fclose(fp);

	char header[1024];
	sprintf(header,
			"HTTP/1.1 %s\r\n"
			"Content-Type: %s\r\n"
			"Content-Length: %zu\r\n"
			"Connection: close\r\n"
			"\r\n",
			is_404 ? "404 Not Found" : "200 OK",
			content_type,
			file_size);

	if (!write(client_sock, header, strlen(header))) {
		// err msg
	}
	if (!write(client_sock, file_buf, file_size)) {
		// err msg
	}
	
	free(file_buf);
}

void handler(void *arg) {
	if (!arg) return;
	printf("[handler]: handler invoked\n");
	_client cnt = *(_client *)arg;
	free(arg);
	size_t MAX_BUFFER = 16 * 1024 * 1024; // 16 MB limit
	char *reqstr = malloc(MAX_BUFFER);
	if (!reqstr) {
		fprintf(stderr, "error: failed to allocate request buffer\n");
		close(cnt.client);
		return;
	}
			       
	printf("1:[handler]: handler invoked\n");
	ssize_t bytes_read = read(cnt.client, reqstr, MAX_BUFFER - 1);
	if (bytes_read <= 0) {
		free(reqstr);
		close(cnt.client);
		return;
	}
	reqstr[bytes_read] = '\0';

	printf("1.5:[handler]: handler invoked\n");

	request *req = request_construct(reqstr);
	free(reqstr); // req string is safely copied inside parser

	printf("2:[handler]: handler invoked\n");
	char *uri = (char *)dict_search(req->req_line, "uri");
	printf("3:[handler]: handler invoked\n");
	printf("4:[handler]: searching for %s\n", uri);  
	route *rte = (route *)dict_search(cnt.server->routes, uri);

	printf("4:[handler]: handler invoked\n");
	if (!rte) {
		serve_fallback(cnt.client, uri); // serve error page
		request_destruct(req);
		close(cnt.client);
		return;
	}

	char* response = rte->route_func(cnt.server, req);

	if (!response) {
		FILE *fp = fopen("files/index.html", "r");
		if (!fp) {
			fprintf(stderr,
					"error: [%s]: failed to open index.html\n",
					__func__);
			exit(1);
		}

		fseek(fp, 0, SEEK_END);
		size_t file_size = (size_t)ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char *file_buf = malloc(file_size + 1);
		if (!file_buf) {
			fprintf(stderr, "error: [%s]: malloc failed\n", __func__);
			fclose(fp);
			exit(1);
		}

		size_t read_sz = fread(file_buf, 1, file_size, fp);
		if (read_sz != file_size) {
			fprintf(stderr,
					"error: [%s]: failed to read complete file\n",
					__func__);
		}
		file_buf[file_size] = '\0';
		fclose(fp);

		response = malloc(file_size + 1024);
		if (!response) {
			fprintf(stderr,
					"error: [%s]: malloc failed for response\n",
					__func__);
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
	printf("5:[handler]: handler invoked\n");
	
	if (write(cnt.client, response, strlen(response)) < 0) {
		fprintf(stderr, "error: failed to write response\n");
	}
	printf("response sent: %s\n", response);

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

		printf("[launch]: 0:about to add work\n");
		cnt->client = (int)accept(http_server->srv->socket, address, &address_length);
		printf("[launch]: 1:about to add work\n");
		cnt->server = http_server;
		printf("[launch]: about to add work\n");

		if (exec_add_work(exec, handler, cnt)) {
			printf("[launch]: work added\n");
		}

	}

}

// void launch(struct http *http_server) {
// 	executor *exec = exec_create(THREAD_CNT);
// 	if (!exec) return;
//
//
// 	//
// 	char buffer[30000];
// 	int new_socket;
//
// 	struct sockaddr *sock_addr =
// 		(struct sockaddr *)&http_server->srv->address;
// 	int addrlen = sizeof(http_server->srv->address);
//
// 	fprintf(stderr, "debug: [%s]: entering server loop\n", __func__);
//
// 	while (1) {
//
// 		printf("=== listening on port %d ===\n", http_server->srv->port);
// 		printf("=== redirect url: http://127.0.0.1:%d ===\n",
// 				http_server->srv->port);
//
// 		new_socket = accept(http_server->srv->socket, sock_addr,
// 				(socklen_t *)&addrlen);
//
// 		ssize_t rdstatus = read(new_socket, buffer, 30000);
// 		request *test = request_construct(buffer);
// 		if (!test)
// 			exit(3);
// 		ssize_t wrtstatus =
// 			write(new_socket, response, strlen(response) + 1);
//
// 		fprintf(stderr, "debug: read status: %zu | write status: %zu\n",
// 				rdstatus, wrtstatus);
//
// 		request_destruct(test);
// 		close(new_socket);
// 	}
// }
