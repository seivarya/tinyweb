/* server.c */

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <server/server.h>

server *server_construct(short unsigned int domain, int service, int protocol,
                         short unsigned int port, int backlog,
                         uint32_t interface) {

        server *srv = malloc(sizeof(server));
        if (!srv) {
                fprintf(stdout, "[%s]: error malloc failed server.c\n", __func__);
                exit(1);
        }

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
                fprintf(stdout, "[%s]: error failed to connect socket server.c\n", __func__);
                exit(1);
        }

        int opt = 1;
        int status = setsockopt(srv->socket, SOL_SOCKET, SO_REUSEADDR, &opt,
                                sizeof(opt));
        if (status) {
                fprintf(stdout, "[%s]: debug time_wait bypassed server.c\n", __func__);
        }

        if ((bind(srv->socket, (struct sockaddr *)&srv->address,
                  sizeof(srv->address))) < 0) {
                fprintf(stdout, "[%s]: error failed to bind socket server.c\n", __func__);
                exit(9);
        }

        if (listen(srv->socket, srv->backlog) < 0) {
                fprintf(stdout, "[%s]: error failed to listen server.c\n", __func__);
                exit(1);
        }

        fprintf(stdout, "[%s]: debug server constructed on port %d server.c\n", __func__, port);
        return srv;
}
