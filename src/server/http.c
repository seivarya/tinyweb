/* http.c */

#include <netinet/in.h>
#include <pthread.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <server/http.h>
#include <server/parser.h>
#include <server/route.h>
#include <server/server.h>
#include <structs/dict/dict.h>

http *http_construct(void) {
        http *http_server = malloc(sizeof(http));

        if (!http_server) {
                fprintf(stderr, "error: [%s]: malloc failed\n", __func__);
                return NULL;
        }

        http_server->srv =
            server_construct(AF_INET, SOCK_STREAM, 0, 1028, 255, INADDR_ANY);

        http_server->routes = dict_construct();
        http_server->launch = launch;

        fprintf(stderr, "debug: [%s]: http server constructed\n", __func__);
        return http_server;
}

char *fetch_page(void) { return "[success]: fetch-page"; }

void register_route(http *srv, char *(*route_func)(http *srv, request *req),
                    char *uri, int count_methods, ...) {

        if (!srv)
                return;

        route *rte = route_construct();

        va_list methods;
        va_start(methods, count_methods);
        for (int i = 0; i < count_methods; i++) {
                rte->methods[i] = va_arg(methods, int);
        }
        strcpy(rte->uri, uri);
        rte->route_func = route_func;
        va_end(methods);
        
        fprintf(stderr, "debug: [%s]: route registered for uri '%s'\n", __func__, uri);
}

void launch(struct http *http_server) {
        FILE *fp = fopen("files/index.html", "r");
        if (!fp) {
                fprintf(stderr,
                        "error: [%s]: failed to open index.html\n",
                        __func__);
                exit(1);
        }

        fseek(fp, 0, SEEK_END);
        size_t file_size = (size_t)ftell(fp);
        fseek(fp, 0, SEEK_SET);

        char *file_buf = malloc(file_size + 1);
        if (!file_buf) {
                fprintf(stderr, "error: [%s]: malloc failed\n", __func__);
                fclose(fp);
                exit(1);
        }

        size_t read_sz = fread(file_buf, 1, file_size, fp);
        if (read_sz != file_size) {
                fprintf(stderr,
                        "error: [%s]: failed to read complete file\n",
                        __func__);
        }
        file_buf[file_size] = '\0';
        fclose(fp);

        char *response = malloc(file_size + 1024);
        if (!response) {
                fprintf(stderr,
                        "error: [%s]: malloc failed for response\n",
                        __func__);
                free(file_buf);
                exit(1);
        }

        sprintf(response,
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "Content-Length: %ld\r\n"
                "Connection: close\r\n"
                "\r\n"
                "%s",
                file_size, file_buf);

        free(file_buf);

        char buffer[30000];
        int new_socket;

        struct sockaddr *sock_addr =
            (struct sockaddr *)&http_server->srv->address;
        int addrlen = sizeof(http_server->srv->address);

        fprintf(stderr, "debug: [%s]: entering server loop\n", __func__);

        while (1) {

                printf("=== listening on port %d ===\n", http_server->srv->port);
                printf("=== redirect url: http://127.0.0.1:%d ===\n",
                       http_server->srv->port);

                new_socket = accept(http_server->srv->socket, sock_addr,
                                    (socklen_t *)&addrlen);

                ssize_t rdstatus = read(new_socket, buffer, 30000);
                request *test = request_construct(buffer);
                if (!test)
                        exit(3);
                ssize_t wrtstatus =
                    write(new_socket, response, strlen(response) + 1);
                
                fprintf(stderr, "debug: read status: %zu | write status: %zu\n",
                       rdstatus, wrtstatus);
                       
                request_destruct(test);
                close(new_socket);
        }
}
