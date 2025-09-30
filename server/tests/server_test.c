#include "../../server/server/server.h"
#include "../../server/http_request/http_request.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

//  INFO: function prototypes

void launch(struct server *server);
void retrieve_page(struct http_request request, int socket);

int main(void) {
	//  WARNING: port used: 1025

	struct server server = server_constructor(AF_INET, SOCK_STREAM, 0, 1025, 10, INADDR_ANY, &launch);
	server.launch(&server);
	printf("=== socket closed ===\n");
}

void launch(struct server *server) {
	int addrlen = sizeof(server->address);
	long valread;

	while(1) {
		printf("=== waiting ===\n");
		printf("=== socket listening on: http://127.0.0.1:1025 ===\n");

		int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&addrlen);

		char buffer[30000];
		read(new_socket, buffer, 30000);

		struct http_request request = http_request_constructor(buffer); // calling http_request_constructor

		//  TEST: tryin' to send generic response

		printf("=== request constructor executed successfully ===\n");

		retrieve_page(request, new_socket);
		close(new_socket);
		printf("=== socket closed ===\n");
	}
}

void retrieve_page(struct http_request request, int socket) {

	char path[30000] = { 0 };
	struct entry * uri_entry = (struct entry *)(request.request_line.dict_search(&request.request_line, "uri"));
	char *url = strtok((char *)(uri_entry->value), "?");
	char *variables = strtok(NULL, "\0"); //  INFO: will return (null) if uri is '/'

	strcpy(path, "server/tests/test_response");

	if (strcmp(url, "/test") == 0) {
		strcat(path, url);

	} else {
		strcat(path, "/index");
	}
	strcat(path, ".html"); // append .html in end
	printf("path: %s\n", path);
	FILE *fp = fopen(path, "r");
	printf("here\n");

	if (!fp) {
		perror("fopen failed");
		return; // or handle error
	}
	fseek(fp, 0L, SEEK_END); //  INFO: seek to the end of the file
	long file_size = ftell(fp); //  INFO: after seek we do ftell on file pointer to get it's location and that's the size of file!

	if (file_size < 0) {
		perror("ftell failed");
		fclose(fp);
		return;
	}
	rewind(fp); //  INFO: seeking to go to the beginning

	printf("=== file size is > %ld ===\n", file_size);

	char *buffer = malloc(file_size + 1);
	fread(buffer, 1, file_size, fp);
	fclose(fp);

	char response[30000] = { 0 };
	strcpy(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"); // status line
	strcat(response, buffer);

	printf("=== response constructed successfully, writing it onto socket. ===\n");
	write(socket, response, strlen(response));
	printf("\r\n\r\n");
}

