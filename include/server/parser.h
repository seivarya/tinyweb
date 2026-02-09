#ifndef PARSER_H
#define PARSER_H

enum methods {
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

typedef struct request {
	int method;
	char *uri;
	float version;
} request;

request* request_construct(char *req_str);

#endif
