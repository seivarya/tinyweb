#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

	char request[] = "GET / HTTP/1.1\n"
		"Host: 127.0.0.1:60971\n"
		"User-Agent: python-requests/2.32.5\n"
		"Accept-Encoding: gzip, deflate\n"
		"Accept: */*\n"
		"Connection: keep-alive\n";

	char *request_line = strtok(request, "\n");
	printf("request line:: %s\n", request_line);

	char *host_line = strtok(NULL, "\n");
	printf("host line:: %s\n", host_line);

	char *test_val = strtok(NULL, "*");
	printf("test: %s\n", test_val);


	return 0;
}

