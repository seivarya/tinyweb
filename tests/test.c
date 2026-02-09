#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <server/server.h>
#include <server/parser.h>
#include <sys/socket.h>

void launch(server *srv);

int main(void) {
	server *srv = server_construct(AF_INET, SOCK_STREAM, 0, 1028, 10, INADDR_ANY); // args/?
	launch(srv);
}

void launch(server *srv) {
	while(1) {
		char buffer[16000]; // temp
		printf("===+ waiting for connection +===\n");

		const char* hello =
			"HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: 48\r\n"
			"Connection: close\r\n"
			"\r\n"
			"<html><body><h1>Hello, World!</h1></body></html>";

		int addrlen = sizeof(srv->address);
		int new_socket = accept(srv->socket, (struct sockaddr *)&srv->address, (socklen_t *)&addrlen);

		ssize_t rdstatus = read(new_socket, buffer, 16000);
		request *test = request_construct(buffer);
		if (!test) exit(3);
		// printf("%s\n", buffer);
		ssize_t wrtstatus = write(new_socket, hello, strlen(hello));
		printf("==+ read status: %zu +==\n==+ write status: %zu +==\n", rdstatus, wrtstatus);
	}
}

