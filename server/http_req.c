#include "http_req.h"
#include "../data_structures/queue/queue.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum http_methods parse_method(const char *method);

struct http_request http_request_constructor(char *request_string_arg) {

	struct http_request request;

	if(!request_string_arg) {
		printf("=== request string not found! ===\n");
		exit(1);
	}

	char request_string[strlen(request_string_arg)];
	strcpy(request_string, request_string_arg); // since

	printf("=== http_request contructor invoked ===\n");


	printf("request total length: %ld\n", strlen(request_string));

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
	char *header_fields = strtok(NULL, "|"); // fetch till modified | char as header fields...
	char *body = strtok(NULL, "|");
	char *method = strtok(request_line, " ");

	request.method = parse_method(method);

	char *URI = strtok(NULL, " ");

	request.URI = URI;

	char *http_version = strtok(NULL, " ");
	http_version = strtok(http_version, "/");
	http_version = strtok(NULL, "/");

	request.http_version  = (float)atof(http_version);

	request.header_fields = dict_constructor(compare_string_keys); // dict init

	struct queue headers_queue= queue_constructor();

	char *token = strtok(header_fields, "\n");
	
	while(token) {
		printf("token > %s\n", token);
		headers_queue.push(&headers_queue, token, strlen(token) + 1);  
		token = strtok(NULL, "\n");
	}

	char *header = (char *)(((struct node *)headers_queue.peek(&headers_queue))->data);
	printf("header string; %s\n", header);

	while(header) {
		char *key = strtok(header, ":");
		char *value = strtok(NULL, "|"); // new line for now

		printf("key > %s\n", key);
		printf("value > %s\n", value);

		request.header_fields.dict_insert(&request.header_fields, key, (int)strlen(key) + 1, value, (int)strlen(value) + 1);
		headers_queue.pop(&headers_queue);
		header = (char *)(((struct node *)headers_queue.peek(&headers_queue))->data);
	}

	return request;
}

enum http_methods parse_method(const char *method) {

	if(strcmp(method, "GET") == 0) return GET;

	if(strcmp(method, "POST") == 0) return POST;

	if(strcmp(method, "PUT") == 0) return PUT;

	if(strcmp(method, "HEAD") == 0) return HEAD;

	if(strcmp(method, "PATCH") == 0) return PATCH;

	if(strcmp(method, "DELETE") == 0) return DELETE;

	if(strcmp(method, "CONNECT") == 0) return CONNECT;

	if(strcmp(method, "OPTIONS") == 0) return OPTIONS;

	if(strcmp(method, "TRACE") == 0) return TRACE;

	printf("=== parse_method returns UNKNOWN ===\n");

	return UNKNOWN; // incase method parsing goes wrong
}
