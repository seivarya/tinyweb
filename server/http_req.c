#include "http_req.h"
#include "../data_structures/queue/queue.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void extract_header_fields(struct http_request *request, char *header_fields);
void extract_request_line_fields(struct http_request *request, char *request_line);
void extract_body(struct http_request *request, char *body);


struct http_request http_request_constructor(char *request_string_arg) {

	struct http_request request;

	if(!request_string_arg) {
		printf("=== request string not found! ===\n");
		exit(1);
	}

	char request_string[strlen(request_string_arg)];
	strcpy(request_string, request_string_arg); // since

	printf("REQUEST TOTAL LENGTH: %ld\n", strlen(request_string));

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

	printf("REQUEST_LINE BEFORE PASSING TO PRIV FUNC. %s\n", request_line);
	printf("HEADER_FIELDS BEFORE PASSING TO PRIV FUNC. %s\n", header_fields);
	/* printf("BODY BEFORE PASSING TO PRIV FUNC. %s\n", body); */
	/* char *method = strtok(request_line, " "); */

	extract_request_line_fields(&request, request_line);
	extract_header_fields(&request, header_fields); // extracting header fields

	/* extract_body(&request, body); */

	return request;
}

void extract_request_line_fields(struct http_request *request, char *request_line) {
	char *uri, *http_version, *method;
	char fields[strlen(request_line)];
	strcpy(fields, request_line); // copy the str literal to local inst.

	method = strtok(fields, " "); 
	uri = strtok(NULL, " ");

	http_version = strtok(NULL, "\0");

	struct dictionary request_line_dict = dict_constructor(compare_string_keys);

	request_line_dict.dict_insert(&request_line_dict, "method", sizeof("method"), method, strlen(method) + 1);
	request_line_dict.dict_insert(&request_line_dict, "uri", sizeof("uri"), uri, strlen(uri) + 1);
	request_line_dict.dict_insert(&request_line_dict, "http_version", sizeof("http_version"), http_version, strlen(http_version) + 1);

	request->request_line = request_line_dict; // assigning the contructed dictionary to request_line
	

	char *test = "method";
	struct entry *fetched_val = request_line_dict.dict_search(&request_line_dict, &test); 
	char *val = (char *)fetched_val->value;

	printf("test_value: %s\n", val);
	printf("INSERTED METHOD: %s\n", method);
	printf("INSERTERD URI: %s\n", uri);
	printf("INSERTED HTTP_VERSION: %s\n", http_version);
}

void extract_header_fields(struct http_request *request, char *header_fields) {
	char fields[strlen(header_fields)];
	strcpy(fields, header_fields);

	struct queue headers = queue_constructor();

	char *token = strtok(fields, "\n");
	
	while(token) {
		printf("TOKEN ABOUT TO BE PUSHED > %s\n", token);
		headers.push(&headers, token, strlen(token) + 1);

		token = strtok(NULL, "\n");
	}

	char *header;
	struct node *node = headers.peek(&headers);
	struct dictionary header_fields_dict = dict_constructor(compare_string_keys);

	if(node) {
		header = (char *)node->data;
	} else {
		header = NULL;
	}

	while(header) {
		char *key = strtok(header, ":");
		char *value = strtok(NULL, "\0"); // ???what

		printf("KEY TO BE INSERTED > %s\n", key);
		printf("VALUE TO BE INSERTED > %s\n", value);

		header_fields_dict.dict_insert(&header_fields_dict, key, (int)(strlen(key) + 1), value, (int)(strlen(value) + 1));

		headers.pop(&headers);

		node = headers.peek(&headers);

		if (node) {
			header = (char *)(node->data);
		} else {
			header = NULL;
		}
	}
		
}
void extract_body(struct http_request *request, char *body) {
	printf("body extracted successfully\n");
}

void http_request_destructor(struct http_request *request) {

	dict_destructor(&request->request_line);
	dict_destructor(&request->header_fields);
	dict_destructor(&request->body);

	printf("=== http_request struct destroyed ===\n");
}

