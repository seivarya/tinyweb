#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <server/parser.h>

request* request_construct(char *req_str) {
	request *req = malloc(sizeof(request));

	if (!req_str) {
		perror("==+ Error: request string not found! +==\n");
		return NULL;
	}

	for (size_t i = 0; i < strlen(req_str); i++) {
		if (req_str[i] == '\n' && req_str[i + 1] == '\n') {
			req_str[i] = '|';
		}
	}
	char *reqline = strtok(req_str, "\n");
	char *headers = strtok(NULL, "|");
	char *body = strtok(NULL, "|"); // extracts the whole thing that's left
	
	printf("request line: %s\n", reqline);
	printf("headers: %s\n", headers);
	printf("body: %s\n", body);
	return req;
}

// GET / HTTP/1.1
// Host: 127.0.0.1:1028
// User-Agent: python-requests/2.32.5
// Accept-Encoding: gzip, deflate, zstd
// Accept: */*
// Connection: keep-alive



