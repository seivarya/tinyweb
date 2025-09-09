#include "server.h"
#include <stdio.h>
#include <stdbool.h>

void launch(struct server *server) {
	int address_length = sizeof(server->address);
	while(true) {
		printf("=== waiting ===");
		int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
	}
}

int main(void) {
	struct server server = server_constructor(AF_INET, SOCK_STREAM, 0, 80, 10, INADDR_ANY, );
}


