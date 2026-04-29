/* http.h */

#ifndef HTTP_H
#define HTTP_H

#include <server/parser.h>
#include <server/server.h>
#include <structs/dict/dict.h>

typedef struct http {
        server *srv;
        dict *routes;
        void (*launch)(struct http *http_server);
} http;

http *http_construct(void);

void register_route(http *srv, char *(*route_func)(http *srv, request *req),
                    char *uri, int count_methods,
                    ...); /* for multiple routes within the site */
char *fetch_page(void);
void launch(struct http *http_server);

#endif /* http.h */
