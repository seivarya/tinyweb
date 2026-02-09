#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


#include <server/server.h>

server* server_construct(short unsigned int domain, int service, int protocol, short unsigned int port, int backlog, uint32_t interface) {

	server *srv = malloc(sizeof(server));

	srv->domain = domain;
	srv->service = service;
	srv->protocol = protocol;
	srv->port = port;
	srv->backlog = backlog;
	srv->interface = interface;
	srv->address.sin_family = domain;
	srv->address.sin_port = htons(port);
	srv->address.sin_addr.s_addr = htonl(interface);
	srv->socket = socket(domain, service, protocol);

	if (srv->socket < 0) {
		perror("==+ ERROR: Failed to connect socket +==\n");
		exit(1);
	}

	int opt = 1;
	int status = setsockopt(srv->socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (status) { printf("TIME_WAIT bypassed\n"); }

	if ((bind(srv->socket, (struct sockaddr *)&srv->address, sizeof(srv->address))) < 0) {
		perror("=== failed to bind socket ===\n");
		exit(9);
	}


	if (listen(srv->socket, srv->backlog) < 0) {
		perror("=== failed to listen === \n");
		exit(1);
	}

	return srv;
}
