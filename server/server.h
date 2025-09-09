#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>

struct server {

	int domain;
	int service;
	int protocol;
	int port;
	int backlog;

	u_long interface;

	struct sockaddr_in address; //  WARNING: maybe ipv6 should be added instead of ipv4?
	int socket;

	void (*launch)(struct server *server);
};

struct server server_constructor(int domain, int service, int protocol, int port, int backlog, u_long interface, void (*launch)(struct server *server));

#endif /* SERVER_H */
