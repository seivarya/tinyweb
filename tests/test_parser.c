#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <server/parser.h>

static void test_no_crlf(void) {
	char req_str[] = "GET / HTTP/1.1\r\nHost: localhost"; 
	request *req = request_construct(req_str);

	assert(req != NULL);
	assert(req->body == NULL); 

	request_destruct(req);
	fprintf(stdout, "[%s]: debug passed test_no_crlf\n", __func__);
}

static void test_mt_hdr(void) {
	char req_str[] = "GET / HTTP/1.1\r\n\r\nBody"; 
	request *req = request_construct(req_str);

	assert(req != NULL);
	assert(req->headers != NULL);

	request_destruct(req);
	fprintf(stdout, "[%s]: debug passed test_mt_hdr\n", __func__);
}

static void test_uri_ext(void) {
	char req_str[] = "POST /api/submit HTTP/1.1\r\nHost: localhost\r\n\r\n";
	request *req = request_construct(req_str);

	assert(req != NULL);
	assert(req->req_line != NULL);

	char *uri = (char *)dict_search(req->req_line, "uri");
	assert(uri != NULL);
	assert(strcmp(uri, "/api/submit") == 0);

	char *method = (char *)dict_search(req->req_line, "method");
	assert(method != NULL);
	assert(strcmp(method, "POST") == 0);

	request_destruct(req);
	fprintf(stdout, "[%s]: debug passed test_uri_ext\n", __func__);
}

int main(void) {
	fprintf(stdout, "[%s]: debug running parser tests\n", __func__);
	test_no_crlf();
	test_mt_hdr();
	test_uri_ext();
	fprintf(stdout, "[%s]: debug all parser tests passed\n", __func__);
	return 0;
}
