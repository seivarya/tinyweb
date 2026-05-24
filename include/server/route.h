/* route.h */

#ifndef ROUTE_H
#define ROUTE_H

#define METHOD_COUNT 9

#include <server/http.h>

typedef struct route {
        int methods[METHOD_COUNT];
        char *uri;
        char *(*route_func)(http *srv, request *req);
} route;

route *route_construct(void);

#endif /* route.h */
