#ifndef PARSER_H
#define PARSER_H

#include <structs/dict.h>

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
	dict *body;
	dict *req_line;
	dict *headers;
} request;

request* request_construct(char *req_str);
void request_destruct(request *req);

void extract_reqline(request *req, char *reqline);
void extract_header(request *req, char *headers);


#endif
