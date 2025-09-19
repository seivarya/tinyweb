#ifndef HTTP_REQ_H
#define HTTP_REQ_H

#include "../data_structures/dictionary/dictionary.h"

enum http_methods {
	GET,
	POST,
	PUT,
	HEAD,
	PATCH,
	DELETE,
	CONNECT,
	OPTIONS,
	TRACE,
	UNKNOWN
};

struct http_request {
	struct dictionary body;
	struct dictionary request_line;
	struct dictionary header_fields;
};

struct http_request http_request_constructor(char * request_string);
void http_request_destructor(struct http_request *request);

#endif /* HTTP_REQ_H */
