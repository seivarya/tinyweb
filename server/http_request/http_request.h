#ifndef HTTP_REQ_H
#define HTTP_REQ_H

#include "../../data_structures/dictionary/dictionary.h"

//  INFO: http methods enum
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

//  INFO: http request object initialization

struct http_request {
	struct dictionary body;
	struct dictionary request_line;
	struct dictionary header_fields;
};

//  INFO: methods

struct http_request http_request_constructor(char * request_string);
void http_request_destructor(struct http_request *request);


//  INFO: function prototypes

void extract_header_fields(struct http_request *request, char *header_fields);
void extract_request_line_fields(struct http_request *request, char *request_line);
void extract_body(struct http_request *request, char *body);


#endif /* HTTP_REQ_H */
