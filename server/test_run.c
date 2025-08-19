#include <stdio.h>
#include "server.h"
#include <unistd.h>
#include <string.h>


void launch(struct server *server) {
	int new_socket;
	char *body = "is it true?";
	char response[4096]; // increase it according to the need.

	sprintf(response,
	 "HTTP/1.0 200 OK\r\n"
	 "Content-Length: %zu\r\n"
	 "Content-Type: text/plain\r\n"
	 "\r\n\n"
	 "%s", strlen(body), body);

	int address_length = sizeof(server->address);
	while(1) {
		printf("waiting...\n");

		char buffer[30000];

		new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
		read(new_socket, buffer, 30000);

		printf("%s\n", buffer);

		write(new_socket, response, strlen(response));
		close(new_socket);
	}
	printf("finished...\n");
}

int main() {

	struct server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 00, 10, launch);
	server.launch(&server);
}
