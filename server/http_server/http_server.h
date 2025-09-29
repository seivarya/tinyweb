#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "../server/server.h"
#include "../http_request/http_request.h"

struct http_server {
	struct server server;
	struct dictionary routes;

	void (*register_routes)(struct http_server *server, void (*route_function)(struct server *server, struct http_request *request), char *uri, int num_methods, ...);
};

struct http_server http_server_constructor(void);


#endif
