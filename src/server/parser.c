#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <server/parser.h>
#include <structs/dict.h>
#include <structs/queue.h>

request* request_construct(char* req_str) {
	request *req = malloc(sizeof(request));

	if (!req_str) {
		perror("==+ Error: request string not found! +==\n");
		return NULL;
	}
	char *reqstr = malloc(strlen(req_str) + 1);
	memcpy(reqstr, req_str, strlen(req_str) + 1);

	size_t len = strlen(reqstr);

	for (size_t i = 0; i + 3 < len; i++) {
		if (reqstr[i] == '\r' &&
			reqstr[i + 1] == '\n' &&
			reqstr[i + 2] == '\r' &&
			reqstr[i + 3] == '\n') {
			reqstr[i] = '|';
			break;
		}
	}
	char *req_line = strtok(reqstr, "\r\n");
	char *headers = strtok(NULL, "|");
	char *body = strtok(NULL, "|");
	printf("=== request line before passing > %s ===\n", req_line);
	printf("=== header fields before passing > %s ===\n", headers);
	printf("=== body before passing > %s ===\n", body);

	extract_reqline(req, req_line);
	extract_header(req, headers);

	return req;
}

void extract_reqline(request *req, char *reqline) {
	char *uri, *version, *method;

	char *fields = malloc(strlen(reqline) + 1);
	memcpy(fields, reqline, strlen(reqline) + 1);

	method = strtok(fields, " ");
	uri = strtok(NULL, " ");
	version = strtok(NULL, "\0");
	printf("=== extract_reqline: invoked ===\n");

	printf("method: %s\n", method);
	printf("uri: %s\n", uri);
	printf("version: %s\n", version);

	req->req_line = dict_construct();

	dict_insert(req->req_line, "method", method);
	dict_insert(req->req_line, "uri", uri);
	dict_insert(req->req_line, "version", version);

	char* method_string = dict_search(req->req_line, "method");
	printf("fetched method_string: %s\n", method_string);
}

void extract_header(request *req, char *headers) {
	char *fields = malloc(strlen(headers) + 1);
	memcpy(fields, headers, strlen(headers) + 1);

	queue *q = queue_construct();
	char *token = strtok(fields, "\n");

	while(token) {
		enqueue(q, token , strlen(token) + 1); // char**
		token = strtok(NULL, "\n");
	}

	char *header;
	qnode *node = (qnode *)get_front(q);
	req->headers = dict_construct();

	if (node) {
		header = (char *)node->data;
	} else {
		header = NULL;
	}

	while(header) {
		char *key = strtok(header, ":");
		char *value = strtok(NULL, "\0");
		printf("key: %s\nvalue: %s\n", key, value);
		dict_insert(req->headers, key, value);

		dequeue(q);
		node = (qnode *)get_front(q);

		if (node) {
			header = (char *)node->data;
		} else {
			header = NULL;
		}
	}

}

void request_destruct(request *req) {
	free(req);
}

