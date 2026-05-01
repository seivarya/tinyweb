/* http.h */

#ifndef HTTP_H
#define HTTP_H

#include <server/parser.h>
#include <server/server.h>
#include <structs/dict/dict.h>

typedef struct http {
	server *srv;
	dict *routes;
	char static_dir[256];
	void (*launch)(struct http *http_server);
} http;

http* http_construct(void);
void register_static_dir(http *srv, const char *dir_path);

void register_route(http *srv, char *(*route_func)(http *srv, request *req),
		char *uri, int count_methods,
		...); /* for multiple routes within the site */
void launch(struct http *http_server);
void handler(void *arg);
char* render_func(const char *status, int file_count, ...);

#endif /* http.h */
