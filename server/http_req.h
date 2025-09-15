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
	int method;
	char *URI;
	float http_version; 
	struct dictionary header_fields;
};

struct http_request http_request_constructor(char * request_string);

#endif /* HTTP_REQ_H */
