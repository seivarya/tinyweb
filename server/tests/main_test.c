#include "../http_request/http_request.h"
#include "../http_server/http_server.h"


int main(void) {
	char *request_string =
		"GET /index.html HTTP/1.1\r\n"
		"Host: localhost\r\n"
		"User-Agent: test-client\r\n"
		"Accept: */*\r\n"
		"\r\n";
	struct http_request request = http_request_constructor(request_string);
	struct http_server server = http_server_constructor();
}
