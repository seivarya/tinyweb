
#include <stdlib.h>
#include <stdio.h>

#include <server/server.h>
#include <server/http.h>
#include <server/parser.h>
#include <structs/dict.h>


http* http_construct(void) {
	http *http_server = malloc(sizeof(http));

	if (!http_server) {
		return NULL;
	}
	
	http_server->srv = server_construct(AF_INET, SOCK_STREAM, 0, 1028, 10, INADDR_ANY);
	http_server->routes = dict_construct();
	http_server->launch = launch;

	return http_server;
}

void (*register_routes)(server *srv, void (*func_route)(server *srv, request *req), char *uri, int methods, ...); // for multiple routes within the site
void launch(server *srv) {

}

char* fetch_page(void) {

}
