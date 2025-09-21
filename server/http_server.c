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
