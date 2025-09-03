#ifndef HTTP_REQ_H
#define HTTP_REQ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data_structures/dictionary/dictionary.h"  // TODO: add data structures here.
 
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
	char *uri;
	float version;
	// TODO: since the headers have a key-value kind of structure so i can convert it to dictionary or follow tuto and use BT
};

struct http_request http_request_constructor(char *request_string);

#endif /* HTTP_REQ_H */
