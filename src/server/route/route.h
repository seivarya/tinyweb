#ifndef ROUTE_H
#define ROUTE_H

#include "../http_request/http_request.h"
#include "../http_server/http_server.h"

struct route {

	int methods[9]; //  INFO: total default methods count: 9
	char *uri;
	char * (*route_function)(struct http_server *server, struct http_request *request);
};

#endif /* ROUTE_H */
