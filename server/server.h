#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h> 
#include <sys/types.h>

struct server {

	int domain;
	int service;
	int protocol;

	unsigned long interface;
	int port;

	int backlog;
	
	struct sockaddr_in address;

	int socket;

	void(*launch)(struct server *server); // for launching server.

};


struct server server_constructor(int domain, int service, int protocol, unsigned long interface, int port, int backlog, void(*launch)(struct server *server)); // function prototype

#endif /*SERVER_H*/
