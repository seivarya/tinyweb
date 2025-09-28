#include "server.h"
#include <stdio.h>
#include <stdlib.h>


struct server server_constructor(int domain, int service, int protocol, int port, int backlog, uint32_t interface, void (*launch)(struct server *server)) {

	printf("=== constructor invoked ===\n");

	struct server server;

	server.domain = domain;
	server.service = service;
	server.protocol = protocol;
	server.port = port;
	server.backlog = backlog;

	server.interface = interface;

	server.address.sin_family = domain;

	server.address.sin_port = htons(port);
	server.address.sin_addr.s_addr = htonl(interface);

	server.socket = socket(domain, service, protocol);

	if (server.socket == 0) {
		perror("=== failed to connect socket ===\n");
		exit(1);
	}

	if ((bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address))) < 0) {
		perror("=== failed to bind socket ===\n");
		exit(9);
	}

	listen(server.socket, server.backlog);

	if (listen(server.socket, server.backlog) < 0) {
		perror("=== failed to listen === \n");
		exit(1);
	}

	server.launch = launch;

	return server;
}
