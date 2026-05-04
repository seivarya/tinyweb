/* parser.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <server/parser.h>
#include <structs/dict/dict.h>
#include <structs/queue/queue.h>

request *request_construct(char *req_str) {
	request *req = malloc(sizeof(request));
	req->body = NULL;
	req->req_line = NULL;
	req->headers = NULL;

	if (!req_str) {
		fprintf(stderr, "[ERROR]: %s :: request string is null\n", __func__);
		free(req);
		return NULL;
	}
	char *reqstr = malloc(strlen(req_str) + 1);
	memcpy(reqstr, req_str, strlen(req_str) + 1);

	size_t len = strlen(reqstr);

	for (size_t i = 0; i + 3 < len; i++) {
		if (reqstr[i] == '\r' && reqstr[i + 1] == '\n' &&
				reqstr[i + 2] == '\r' && reqstr[i + 3] == '\n') {
			reqstr[i] = '|';
			break;
		}
	}
	char *req_line = strtok(reqstr, "\r\n");
	char *headers = strtok(NULL, "|");
	char *body = strtok(NULL, "|");

	fprintf(stdout, "[DEBUG]: %s :: req_line > %s\n", __func__, req_line);
	fprintf(stdout, "[DEBUG]: %s :: headers > %s\n", __func__, headers);
	fprintf(stdout, "[DEBUG]: %s :: body > %s\n", __func__, body);

	extract_reqline(req, req_line);
	extract_header(req, headers);

	fprintf(stdout, "[DEBUG]: %s :: request constructed\n", __func__);
	free(reqstr);
	return req;
}

void extract_reqline(request *req, char *reqline) {
	if (!req || !reqline) {
		fprintf(stderr, "[ERROR]: %s :: null req or reqline pointer\n", __func__);
		return;
	}
	char *uri, *version, *method;

	char *fields = malloc(strlen(reqline) + 1);
	memcpy(fields, reqline, strlen(reqline) + 1);

	method = strtok(fields, " ");
	uri = strtok(NULL, " ");
	version = strtok(NULL, "\0");

	fprintf(stdout, "[DEBUG]: %s :: method=%s uri=%s version=%s\n", __func__, method, uri, version);

	req->req_line = dict_construct();

	dict_insert(req->req_line, "method", method, strlen(method) + 1);
	dict_insert(req->req_line, "uri", uri, strlen(uri) + 1);
	dict_insert(req->req_line, "version", version, strlen(version) + 1);

	char *method_string = (char *)dict_search(req->req_line, "method");
	fprintf(stdout, "[DEBUG]: %s :: verified method in dict: %s\n", __func__, method_string);

	free(fields);
}

void extract_header(request *req, char *headers) {
	if (!req || !headers) {
		fprintf(stderr, "[ERROR]: %s :: null req or headers pointer\n", __func__);
		return;
	}
	char *fields = malloc(strlen(headers) + 1);
	memcpy(fields, headers, strlen(headers) + 1);

	queue *q = queue_construct();
	char *token = strtok(fields, "\n");

	while (token) {
		enqueue(q, token, strlen(token) + 1); /* char** */
		token = strtok(NULL, "\n");
	}

	char *header;
	queue_node *node = (queue_node *)get_front(q);
	req->headers = dict_construct();

	if (node) {
		header = (char *)node->data;
	} else {
		header = NULL;
	}

	while (header) {
		char *key = strtok(header, ":");
		char *value = strtok(NULL, "\0");

		if (key && value) {
			if (value[0] == ' ') value++; /* Trim leading space */
			fprintf(stdout, "[DEBUG]: %s :: header parsed: '%s' = '%s'\n", __func__, key, value);
			dict_insert(req->headers, key, value, strlen(value) + 1);
		} else {
			fprintf(stderr, "[ERROR]: %s :: malformed header line skipped\n", __func__);
		}

		dequeue(q); /* inserting key, value in dict and dequeuing that pair */

		node = (queue_node *)get_front(q);

		if (node) {
			header = (char *)node->data;
		} else {
			header = NULL;
			break;
		}
	}
	queue_destruct(q);
	free(fields);
}

void request_destruct(request *req) {
	if (!req) {
		fprintf(stderr, "[ERROR]: %s :: null request pointer\n", __func__);
		return;
	}
	if (req->req_line) dict_destruct(req->req_line);
	if (req->headers) dict_destruct(req->headers);
	fprintf(stdout, "[DEBUG]: %s :: request destructed\n", __func__);
	free(req);
}
