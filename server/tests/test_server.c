#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../http_server/http_server.h"

void retrieve_page();

int main(void) {
	struct http_server http_server = http_server_constructor();

	http_server.launch(&http_server);
	return 0;
}



