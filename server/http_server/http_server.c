#include "../route/route.h"
#include "http_server.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>


void (register_routes)(struct http_server *server, void (*route_function)(struct server *server, struct http_request *request), char *uri, int num_methods, ...);

void launch(struct server *server);

struct http_server http_server_constructor() {
	struct http_server server;

	server.server = server_constructor(AF_INET, SOCK_STREAM, 0, 1025, 255, INADDR_ANY); 	
	server.register_routes = register_routes;
	server.routes = dict_constructor(compare_string_keys); //  WARNING: remove str key later.

	return server;
}

void register_routes(struct http_server *server, void (*route_function)(struct server *server, struct http_request *request), char *uri, int num_methods, ...) {

	printf("=== register_routes invoked ===\n");

	struct route route;
	va_list methods;

	va_start(methods, num_methods);

	for(int i = 0; i < num_methods; i++) {
		route.methods[i] = va_arg(methods, int);
	}
	strcpy(route.uri, uri);

	/* route.route_function = route_function; */  //  FIX: add route_function

	server->routes.dict_insert(&server->routes, uri, strlen(uri) + 1, &route, sizeof(route));
}

//  INFO: just a test launch function, to be removed later

void launch(struct server *server) {

	int addrlen = sizeof(server->address);
	long valread;

	while(1) {
		printf("=== launch function triggered === \n");
		printf("=== waiting ===\n");

		int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&addrlen);

		char buffer[30000];
		valread = read(new_socket, buffer, 30000);

		struct http_request request = http_request_constructor(buffer); // calling http_request_constructor

		//  TEST: tryin' to send generic response

		printf("=== request constructor executed successfully ===\n");

		close(new_socket);
	}
}

