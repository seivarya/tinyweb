#include <server/http.h>

#ifndef ROUTE_H
#define ROUTE_H
typedef struct route {
        int methods[9];
        char *uri;
        char *(*route_func)(http *srv, request *req);
} route;

route *route_construct(void);

#endif
