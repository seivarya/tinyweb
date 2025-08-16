#include <stdio.h>
#include "server.h"
#include <stdlib.h>

struct server server_constructor(int domain, int service, int protocol, unsigned long interface, int port, int backlog, void(*launch)(struct server *server)) {
	struct server server;

	server.domain = domain;
	server.service = service;
	server.interface = interface;
	server.port = port;
	server.backlog = backlog;

	server.address.sin_family = domain;
	server.address.sin_port = htons(port);
	server.address.sin_addr.s_addr = htonl(interface);

	printf("server.address.sin_port: port >  %u\n", (unsigned)htons(port));
	printf("server.address.sin_addr.s_addr: interface > %u\n", (unsigned)htonl(interface));

	server.socket = socket(domain, service, protocol);
	socklen_t addrlen = sizeof(server.address);
	
	if (server.socket < 0) {
		perror("failed to connect socket....\n");
		exit(1);
	}

	if ((bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address))) < 0) {
		perror("failed to bind socket....\n");
		exit(1);
	}

	if (listen(server.socket, server.backlog) < 0) {
		perror("failed to start listening...\n");
		exit(1);
	}

	if (getsockname(server.socket, (struct sockaddr *)&server.address, &addrlen) == -1) {
		perror("getsockname");
	} else {
		printf("listening on > %u\n", ntohs(server.address.sin_port));
	}

	server.launch = launch;
	return server;
}
