#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

struct server {
	int domain;
	int service;
	int protocol;
	int port;
	int backlog;
	uint32_t interface;
	int socket;
	struct sockaddr_in address;
	void (*launch)(struct server *server);
};

struct server server_constructor(
	int domain,
	int service,
	int protocol,
	int port,
	int backlog,
	uint32_t interface,
	void (*launch)(struct server *server)
);

#endif // SERVER_H
