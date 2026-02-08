#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>
#include <netinet/in.h>

typedef struct server {
	short unsigned int domain;
	int service; // socket type
	int protocol; // 0, IPPROTO_TCP, IPPROTO_UDP
	short unsigned int port;
	int backlog;
	uint32_t interface;
	int socket;
	struct sockaddr_in address;
} server;

server server_construct(
	short unsigned int domain,
	int service,
	int protocol,
	short unsigned int port,
	int backlog,
	uint32_t interface
);

#endif /* server.h */
