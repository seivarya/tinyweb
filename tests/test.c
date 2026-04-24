#include <sys/socket.h>
#include <unistd.h>

#include <server/http.h>
#include <server/parser.h>
#include <server/server.h>

int main(void) {
        http *srvr = http_construct();
        launch(srvr->srv);
}
