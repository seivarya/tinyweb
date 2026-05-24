/* server.h */

#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <stdint.h>

typedef struct server {
        short unsigned int domain;
        int service;  /* socket type */
        int protocol; /* 0, ipproto_tcp, ipproto_udp */
        short unsigned int port;
        int backlog;
        uint32_t interface;
        int socket;
        struct sockaddr_in address;
} server;

server *server_construct(short unsigned int domain, int service, int protocol,
                         short unsigned int port, int backlog,
                         uint32_t interface);

void server_destruct(server *srv);

#endif /* server.h */
