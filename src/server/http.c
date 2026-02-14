
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>


#include <server/http.h>
#include <server/parser.h>
#include <server/route.h>
#include <server/server.h>

#include <structs/dict.h>


http* http_construct(void) {
	http *http_server = malloc(sizeof(http));

	if (!http_server) {
		return NULL;
	}
	
	http_server->srv = server_construct(AF_INET, SOCK_STREAM, 0, 1028, 10, INADDR_ANY);
	http_server->routes = dict_construct();
	http_server->launch = launch;

	return http_server;
}

void launch(server *http_server) {
	char *response =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html; charset=UTF-8\r\n"
		"Content-Length: 3083\r\n"
		"Connection: close\r\n"
		"\r\n"
		"<!DOCTYPE html>\n"
		"<html lang=\"en\">\n"
		"<head>\n"
		"\t<meta charset=\"UTF-8\">\n"
		"\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
		"\t<title>Minimalist Web Server Showcase</title>\n"
		"\t<script src=\"https://cdn.tailwindcss.com\"></script>\n"
		"\t<style>\n"
		"\tbody {\n"
		"\t\tfont-family: 'Inter', sans-serif;\n"
		"\t}\n"
		"\t</style>\n"
		"</head>\n"
		"<body class=\"bg-gray-50 text-gray-800 flex items-center justify-center min-h-screen p-6\">\n"
		"\n"
		"\t<div class=\"bg-white rounded-2xl shadow-lg max-w-3xl w-full p-10\">\n"
		"\n"
		"\t\t<!-- Header -->\n"
		"\t\t<header class=\"text-center mb-10\">\n"
		"\t\t\t<h1 class=\"text-5xl font-extrabold text-green-600 mb-3\">\n"
		"\t\t\t\tMy Minimalist Web Server\n"
		"\t\t\t</h1>\n"
		"\t\t\t<p class=\"text-gray-600 text-lg\">\n"
		"\t\t\t\tServing static and dynamic content directly from a lightweight C-based server.\n"
		"\t\t\t</p>\n"
		"\t\t</header>\n"
		"\n"
		"\t\t<!-- Main Content -->\n"
		"\t\t<main class=\"space-y-8\">\n"
		"\n"
		"\t\t\t<!-- Section 1 -->\n"
		"\t\t\t<section class=\"border-b border-gray-200 pb-6\">\n"
		"\t\t\t\t<h2 class=\"text-2xl font-semibold text-gray-700 mb-2\">\n"
		"\t\t\t\t\tAbout This Server\n"
		"\t\t\t\t</h2>\n"
		"\t\t\t\t<p class=\"text-gray-600 leading-relaxed\">\n"
		"\t\t\t\t\tThis web server is a minimal, yet fully functional HTTP server written in C. It listens for incoming requests, parses HTTP methods, locates the requested resources, and sends precise HTTP responses back to the client. Unlike typical heavy frameworks, this server demonstrates the core networking principles, threading, and file I/O required for web communication in a compact, efficient package.\n"
		"\t\t\t\t</p>\n"
		"\t\t\t</section>\n"
		"\n"
		"\t\t\t<!-- Section 2 -->\n"
		"\t\t\t<section class=\"border-b border-gray-200 pb-6\">\n"
		"\t\t\t\t<h2 class=\"text-2xl font-semibold text-gray-700 mb-2\">\n"
		"\t\t\t\t\tHow It Works\n"
		"\t\t\t\t</h2>\n"
		"\t\t\t\t<p class=\"text-gray-600 leading-relaxed\">\n"
		"\t\t\t\t\tWhen your browser requests a page, it sends an HTTP <code class=\"bg-gray-100 px-1 rounded\">GET</code> request to the server. The server parses the request headers, determines which file to serve, and constructs a full HTTP response with the correct headers, including <code class=\"bg-gray-100 px-1 rounded\">Content-Type</code> and <code class=\"bg-gray-100 px-1 rounded\">Content-Length</code>. Once the response is ready, it is transmitted back to the client over TCP, and your browser renders the HTML content seamlessly.\n"
		"\t\t\t\t</p>\n"
		"\t\t\t</section>\n"
		"\n"
		"\t\t\t<!-- Section 3 -->\n"
		"\t\t\t<section>\n"
		"\t\t\t\t<h2 class=\"text-2xl font-semibold text-gray-700 mb-2\">\n"
		"\t\t\t\t\tWhy Minimalism Matters\n"
		"\t\t\t\t</h2>\n"
		"\t\t\t\t<p class=\"text-gray-600 leading-relaxed\">\n"
		"\t\t\t\t\tBy keeping the server minimal, we gain a deep understanding of the underlying principles of HTTP communication, socket programming, and multithreading. This also ensures that the server remains lightweight, efficient, and easy to extend. Future enhancements could include handling <code class=\"bg-gray-100 px-1 rounded\">POST</code> requests, serving multiple content types, implementing thread pools for concurrency, and integrating dynamic content generation.\n"
		"\t\t\t\t</p>\n"
		"\t\t\t</section>\n"
		"\n"
		"\t\t</main>\n"
		"\n"
		"\t\t<!-- Footer -->\n"
		"\t\t<footer class=\"mt-10 text-center text-gray-400 text-sm\">\n"
		"\t\t\t<p>&copy; 2025 @shizvank • Minimalist Web Server. All rights reserved.</p>\n"
		"\t\t</footer>\n"
		"\n"
		"\t</div>\n"
		"\n"
		"</body>\n"
		"</html>\n";

	char buffer[30000];
	int new_socket;

	struct sockaddr *sock_addr = (struct sockaddr *)&http_server->address;
	int addrlen = sizeof(http_server->address);

	while(1) {

		printf("=== Listening on port %d ===\n", http_server->port);
		printf("=== redirect url: http://127.0.0.1:%d ===\n", http_server->port);

		new_socket = accept(http_server->socket, sock_addr, (socklen_t *)&addrlen);

		ssize_t rdstatus = read(new_socket, buffer, 30000);
		request *test = request_construct(buffer);
		if (!test) exit(3);
		ssize_t wrtstatus = write(new_socket, response, strlen(response) + 1);
		printf("%s\n", buffer);

		printf("==+ read status: %zu +==\n==+ write status: %zu +==\n", rdstatus, wrtstatus);
		close(new_socket);
	}

}

char* fetch_page(void) {
	return "smth";
}

void register_route(http *srv, char* (*route_func)(http *srv, request *req), char *uri, int count_methods, ...) {

	if (!srv) return;

	route *rte = route_construct();

	va_list methods;
	va_start(methods, count_methods);
	for (int i = 0; i < count_methods; i++) {
		rte->methods[i] = va_arg(methods, int);
	}
	strcpy(rte->uri, uri);
	rte->route_func = route_func;
	va_end(methods);

}
