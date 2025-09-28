#include "../route/route.h"
#include "http_server.h"

#include <stdarg.h>
#include <string.h>


void (register_routes)(struct server *server, void (*route_function)(struct server *server, struct http_request *request), char *uri, int num_methods, ...);

void test_launch(struct server *server);

struct http_server http_server_constructor() {
	struct http_server server;

	server.server = server_constructor(AF_INET, SOCK_STREAM, 0, 80, 255, INADDR_ANY, test_launch); //  FIX: remove launch later
	server.register_routes = register_routes;
	server.routes = dict_constructor(compare_string_keys); //  WARNING: remove str key later.
	
	return server;
}

void register_routes(struct server *server, void (*route_function)(struct server *server, struct http_request *request), char *uri, int num_methods, ...) {
	
	struct route route;
	va_list methods;

	va_start(methods, num_methods);

	for(int i = 0; i < num_methods; i++) {
		route.methods[i] = va_arg(methods, int);
	}
	strcpy(route.uri, uri);
/* 	route.route_function = route_function; */

	struct http_server server_test = http_server_constructor();
}

