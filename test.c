#include <stdio.h>
#include "server.h"
#include <unistd.h>
#include <string.h>


void launch(struct server *server) {
	int new_socket;
	char *body =
		"<!DOCTYPE html>\n"
		"<html>\n"
		"<head>\n"
		"    <meta charset=\"utf-8\">\n"
		"    <title>web server | home</title>\n"
		"    <style>\n"
		"        body {\n"
		"            background-color: black;\n"
		"            margin: 0;\n"
		"            height: 100vh;\n"
		"            display: flex;\n"
		"            justify-content: center;\n"
		"            align-items: center;\n"
		"            color: white;\n"
		"            font-size: 30px;\n"
		"            font-family: Arial, sans-serif;\n"
		"            text-align: center;\n"
		"        }\n"
		"        p {\n"
		"            margin: 10px 0;\n"
		"        }\n"
		"    </style>\n"
		"</head>\n"
		"\n"
		"<body>\n"
		"    <div>\n"
		"        <p>it works..</p>\n"
		"    </div>\n"
		"</body>\n"
		"</html>\n";

	char response[4096]; // increase it according to the need.

	sprintf(response,
	 "HTTP/1.0 200 OK\r\n"
	 "Content-Length: %zu\r\n"
	 "Content-Type: text/html\r\n"
	 "\r\n"
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
