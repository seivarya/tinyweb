#include "http_req.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


struct http_request http_request_constructor(char * request_string) {
	printf("=== http_request contructor invoked ===\n");

	if(!request_string) {
		printf("=== request string not found! ===\n");
		exit(1);
	}

	printf("request total length: %ld", strlen(request_string));

	size_t len = strlen(request_string);
	for (size_t i = 0; i + 3 < len; i++) {
		if (request_string[i] == '\r' &&
			request_string[i + 1] == '\n' &&
			request_string[i + 2] == '\r' &&
			request_string[i + 3] == '\n') {
			request_string[i] = '|'; break;
		}
	}
	char *request_line = strtok(request_string, "\r\n"); // fetch first instance of \r\n
	char *header_fields = strtok(NULL, "|"); // fetch till modified | char as header fields... might use dict to make it correct key-val pairs
	
	char *body = strtok(NULL, "|");

	struct http_request request;
	char *method = strtok(request_line, " ");
}


/*
 
WARNING: this approach is flawed for now, if the body has | inserted somewhere strtok will break instead of this.

FIX: i dont need to do this strtok buisness! i can just insert | at i + 4 (so as to not modify the req or delimeter of \r\n\r\n and then parse for req_line and header_fields a...after that i can use use \r\n\r\n and skip | once and boomm i've the whole body

*/
