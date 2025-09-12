#include "server/server.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void launch(struct server *server);

int main(void) {
	//  WARNING: i used port: 1025 in my constructor coz 1024 and < 1024 are privileged and can be only used by root users and despite being a root user myself, it's not working in my system.
	
	struct server server = server_constructor(AF_INET, SOCK_STREAM, 0, 1025, 10, INADDR_ANY, &launch);
	server.launch(&server);
	printf("=== socket closed ===\n");
}

void launch(struct server *server) {
	printf("=== server launch invoked ===\n");

	char buffer[30000];
	int address_length = sizeof(server->address);
	int new_socket;

	char *response = 
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html; charset=UTF8\r\n"
		"Content-Length: 2931\r\n"
		"\r\n"
		"<!DOCTYPE html>\n"
		"<html lang=\"en\">\n"
		"<head>\n"
		"    <meta charset=\"UTF-8\">\n"
		"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
		"    <title>My Simple Web Server</title>\n"
		"    <!-- Use the Tailwind CSS CDN for easy styling -->\n"
		"    <script src=\"https://cdn.tailwindcss.com\"></script>\n"
		"    <style>\n"
		"        /* Apply a custom font to the entire body */\n"
		"        body {\n"
		"            font-family: 'Inter', sans-serif;\n"
		"        }\n"
		"    </style>\n"
		"</head>\n"
		"<body class=\"bg-gray text-black-800 flex items-center justify-center min-h-screen p-4\">\n"
		"    <!-- Main container with a nice card-like appearance -->\n"
		"    <div class=\"bg-white p-8 rounded-2xl shadow-xl max-w-2xl w-full\">\n"
		"        <!-- Header section with a title and description -->\n"
		"        <header class=\"text-center mb-8\">\n"
		"            <h1 class=\"text-4xl md:text-5xl font-extrabold text-blue-600 mb-2\">\n"
		"                Hello, World!\n"
		"            </h1>\n"
		"            <p class=\"text-lg text-gray-600\">\n"
		"                This page was served by my very own C web server.\n"
		"            </p>\n"
		"        </header>\n"
		"        <!-- Main content section -->\n"
		"        <main>\n"
		"            <section class=\"mb-6 border-b pb-6\">\n"
		"                <h2 class=\"text-2xl font-semibold text-gray-700 mb-2\">\n"
		"                    About This Server\n"
		"                </h2>\n"
		"                <p class=\"text-gray-600\">\n"
		"                    This is a basic HTML file served directly from a server I built myself. The server is responsible for listening for incoming HTTP requests and sending this file back as a response. This demonstrates the core functionality of a web server.\n"
		"                </p>\n"
		"            </section>\n"
		"            <section class=\"mb-6 border-b pb-6\">\n"
		"                <h2 class=\"text-2xl font-semibold text-gray-700 mb-2\">\n"
		"                    How it Works\n"
		"                </h2>\n"
		"                <p class=\"text-gray-600\">\n"
		"                    When your browser requested this page, it sent an HTTP `GET` request to my server. The server then located this HTML file, prepared an HTTP response with the correct headers (like `Content-Type: text/html`), and sent the data stream back to you. Your browser then rendered the HTML to display this beautiful page.\n"
		"                </p>\n"
		"            </section>\n"
		"            <section>\n"
		"                <h2 class=\"text-2xl font-semibold text-gray-700 mb-2\">\n"
		"                    What's Next?\n"
		"                </h2>\n"
		"                <p class=\"text-gray-600\">\n"
		"                    Now that the basic communication is working, the next step is to add more advanced features! This could include serving more complex pages, handling different types of requests (like `POST`), or even serving dynamic content.\n"
		"                </p>\n"
		"            </section>\n"
		"        </main>\n"
		"        <!-- Footer section -->\n"
		"        <footer class=\"mt-8 text-center text-gray-400 text-sm\">\n"
		"            <p>&copy; 2025 @shizvank: web.server. All rights reserved.</p>\n"
		"        </footer>\n"
		"    </div>\n"
		"</body>\n"
		"</html>\n";

	while(1) {

		printf("=== waiting ===\n=== on port: 1025 ===\n=== link: http://127.0.0.1:1025 ===\n");

		new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
		
		read(new_socket, buffer, 30000);
		printf("%s\n", buffer);


		write(new_socket, response, strlen(response));
		close(new_socket);
		printf("=== socket closed ===\n");
	}
}

