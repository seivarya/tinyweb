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
                fprintf(stderr, "[ERROR]: %s :: malloc failed for server struct\n", __func__);
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
                fprintf(stderr, "[ERROR]: %s :: failed to create socket\n", __func__);
                exit(1);
        }

        int opt = 1;
        int status = setsockopt(srv->socket, SOL_SOCKET, SO_REUSEADDR, &opt,
                                sizeof(opt));
        if (!status) {
                fprintf(stdout, "[DEBUG]: %s :: so_reuseaddr set, time_wait bypassed\n", __func__);
        }

        if ((bind(srv->socket, (struct sockaddr *)&srv->address,
                  sizeof(srv->address))) < 0) {
                fprintf(stderr, "[ERROR]: %s :: failed to bind socket to port\n", __func__);
                exit(9);
        }

        if (listen(srv->socket, srv->backlog) < 0) {
                fprintf(stderr, "[ERROR]: %s :: failed to start listening on socket\n", __func__);
                exit(1);
        }

        fprintf(stdout, "[SUCCESS]: %s :: server constructed on port %d\n", __func__, port);
        return srv;
}

void server_destruct(server *srv) {
        if (!srv) {
                fprintf(stderr, "[ERROR]: %s :: server pointer is null\n", __func__);
                exit(1);
        }
        if (srv->socket > 0) {
                int status = close(srv->socket);
                if (status) {
                        fprintf(stderr, "[ERROR]: %s :: failed to close socket fd\n", __func__);
                        exit(1);
                }
        }
        free(srv);
        fprintf(stdout, "[DEBUG]: %s :: server destructed\n", __func__);
}