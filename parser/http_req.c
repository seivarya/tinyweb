#include <stdio.h>
#include "http_req.h"
#include <string.h>

int select_method(char *method) {
	if (method == NULL) {
		printf("Error: no method found\n");
		return -1;
	} else if (strcmp(method, "GET") == 0) {
		return GET;
	} else if (strcmp(method, "POST") == 0) {
		return POST;
	} else if (strcmp(method, "PUT") == 0) {
		return PUT;
	} else if (strcmp(method, "HEAD") == 0) {
		return HEAD;
	} else if (strcmp(method, "PATCH") == 0) {
		return PATCH;
	} else if (strcmp(method, "DELETE") == 0) {
		return DELETE;
	} else if (strcmp(method, "CONNECT") == 0) {
		return CONNECT;
	} else if (strcmp(method, "OPTIONS") == 0) {
		return OPTIONS;
	} else if (strcmp(method, "TRACE") == 0) {
		return TRACE;
	} else {
		printf("Error: unknown method '%s'\n", method);
		return -1;
	}
}

struct http_request http_request_constructor(char *request_string) {
	printf("invoked http_request struct\n");

	size_t length = strlen(request_string);
	for (int i = 0; i < length - 1; i++) {
		if (request_string[i] == '\n' && request_string[i + 1] == '\n') {
			// replacing the str with '|' where \n\n <content> exists
			request_string[i + 1] = '|';
		}
	}

	char *request_line = strtok(request_string, "\n");
	char *header       = strtok(NULL, "|");
	char *body         = strtok(NULL, "|");

	printf("tokenized output:\n" // TODO: remove after debug later
	       "  1. request line: %s\n"
	       "  2. header: %s\n"
	       "  3. body: %s\n",
	       request_line, header, body);

	struct http_request request;

	char *method = strtok(request_line, " ");
	request.method = select_method(method);

	char *uri = strtok(NULL, " ");
	request.uri = uri;

	char *version = strtok(NULL, " ");
	version = strtok(version, "/");
	char *version_num = strtok(NULL, "/");

	request.version = (float) atof(version_num);

	return request;
}


