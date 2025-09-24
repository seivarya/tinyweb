#include "../server/server.h"
#include "../request_parser/http_req.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

//  INFO: function prototypes

void launch(struct server *server);
void retrieve_page(struct http_request request, int socket);

int main(void) {
	//  WARNING: port used: 1025
	
	struct server server = server_constructor(AF_INET, SOCK_STREAM, 0, 1025, 10, INADDR_ANY, &launch);
	server.launch(&server);
	printf("=== socket closed ===\n");
}

void launch(struct server *server) {
	int addrlen = sizeof(server->address);
	long valread;
	
	while(1) {
		printf("=== launch function triggered === \n");
		printf("=== waiting ===\n");

		int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&addrlen);

		char buffer[30000];
		valread = read(new_socket, buffer, 30000);
		printf("BUFFER START\n %s\nBUFFER END\n", buffer);
		printf("here\n");
		struct http_request request = http_request_constructor(buffer); // calling http_request_constructor
		// TEST: tryin' to send generic response
		
		char *name = "Host";
		struct entry *content_type_entry = request.header_fields.dict_search(&request.header_fields, name);
		char *content_type = (char *)content_type_entry->value;
		
		printf("content type fetched %s\n", content_type);
printf("here four\n");

		char *greet = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\r\n\r\n";

		char r[strlen(greet) + strlen(content_type)];

		strcat(r, greet);
		strcat(r, content_type);

		write(new_socket, r, strlen(r));
		// retrieve_page(request, new_socket);
		close(new_socket);
	}
}

void retrieve_page(struct http_request request, int socket) {

	char *uri = request.request_line.dict_search(&request.request_line, "uri");


	printf("temp val\n");

}
