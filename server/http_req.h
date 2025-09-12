#ifndef HTTP_REQ_H
#define HTTP_REQ_H

enum http_methods {
	GET,
	POST,
	PUT,
	HEAD,
	PATCH,
	DELETE,
	CONNECT,
	OPTIONS,
	TRACE
};

struct http_request {
	int method;
	char *URI;
	float http_version; // HEADERS TO BE ADDED LATER
};

struct http_request http_request_constructor(char * request_string);

#endif /* HTTP_REQ_H */
