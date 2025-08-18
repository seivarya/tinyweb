#include <stdio.h>
#include "http_req.h"
#include <string.h>

struct http_request http_request_constructor(char *request_string) {

	printf("invoked http_request struct\n");

	for(int i = 0; i < strlen(request_string) - 1; i++) {
		if (request_string[i] == '\n' && request_string[i + 1] == '\n' && request_string[i + 2] != '\n') { // replacing the str with '|' where \n\n <content> exists
			request_string[i + 1] = '|';
		}
	}

	char *request_line = strtok(request_string, "\n");
}
