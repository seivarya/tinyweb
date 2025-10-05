#include "../route/route.h"
#include "../thread_pool/thread_pool.h"
#include "http_server.h"


#include <stdio.h>
#include <stdarg.h>
#include <string.h>


void (register_routes)(struct http_server *server, void (*route_function)(struct server *server, struct http_request *request), char *uri, int num_methods, ...);

void launch(struct http_server *http_server);

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

void launch(struct http_server *http_server) {

	struct thread_pool thread_pool = thread_pool_constructor(10); //  FIX: thead default for now

	struct sockaddr *sock_addr = (struct sockaddr *)&http_server->server.address;
	int addr_len = sizeof(http_server->server.address);

	while(1) {
		printf("=== launch function triggered === \n");
		printf("=== waiting ===\n");

		accept(http_server->server.socket, sock_addr, (socklen_t *)&addr_len);

	}

} /* HTTP_SERVER_C */
