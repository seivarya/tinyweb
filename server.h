#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h> 

struct server {

	int domain;
	int service;
	int protocol;
	int backlog;
	int port;

	u_long interface;
	
	struct sockaddr_in6 address;
	void(*launch)(void);

};


struct server server_constructor(int domain, int service, int protocol, int backlog, int port, u_long interface);

#endif /*SERVER_H*/
