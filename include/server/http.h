#ifndef HTTP_H
#define HTTP_H

#include <server/server.h>
#include <server/parser.h>
#include <structs/dict.h>

typedef struct http {
	server *srv;
	dict *routes;
	void (*launch)(server *srv);
} http;

http* http_construct(void);

void (*register_routes)(server *srv, void (*func_route)(server *srv, request *req), char *uri, int methods, ...); // for multiple routes within the site
char* fetch_page(void);
void launch(server *srv);

#endif
