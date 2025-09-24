#include "../server/server.h"
#include "../request_parser/http_req.h"

#include <stdio.h>
#include <stdbool.h>
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

		struct http_request request = http_request_constructor(buffer); // calling http_request_constructor

		// TEST: tryin' to send generic response
		char *name = "Host";
		char *content_type = (char *)request.header_fields.dict_search(&request.header_fields, "Host");

		// retrieve_page(request, new_socket);
		close(new_socket);
	}
}

void retrieve_page(struct http_request request, int socket) {

	printf("temp val\n");

}
