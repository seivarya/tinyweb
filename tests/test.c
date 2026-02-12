#include <unistd.h>
#include <sys/socket.h>

#include <server/server.h>
#include <server/parser.h>
#include <server/http.h>


int main(void) {
	http *srvr = http_construct();
	launch(srvr->srv);
}
