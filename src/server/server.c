#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


#include <server/server.h>

server server_construct(short unsigned int domain, int service, int protocol, short unsigned int port, int backlog, uint32_t interface) {
	server srv = {
		.domain = domain,
		.service = service,
		.protocol = protocol,
		.port = port,
		.backlog = backlog,
		.interface = interface,
		.address.sin_family = domain,
		.address.sin_port = htons(port),
		.address.sin_addr.s_addr = htonl(interface),
		.socket = socket(domain, service, protocol)
	};

	if (srv.socket < 0) {
		perror("==+ ERROR: Failed to connect socket +==\n");
		exit(1);
	}

	if ((bind(srv.socket, (struct sockaddr *)&srv.address, sizeof(srv.address))) < 0) {
		perror("=== failed to bind socket ===\n");
		exit(9);
	}


	if (listen(srv.socket, srv.backlog) < 0) {
		perror("=== failed to listen === \n");
		exit(1);
	}

	return srv;
}
