#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>

#include "cmd/init.h"
#include "pkg/errors.h"


int main(int argc, char** argv) {
    struct InitParams params = parse_args(argc, argv);
    struct sockaddr_in address = init_address(params.port);
    int socket_descriptor = init_socket((struct sockaddr*)&address, params.connection_number);
    struct sockaddr_in peer;
    int peer_descriptor;

    int peer_size = sizeof(peer);
    peer_descriptor = accept(socket_descriptor, (struct sockaddr*)&peer, &peer_size);
    if (peer_descriptor < 0) {
        server_error_handler("Error accept request", Info);
    }

    send(peer_descriptor, "hello!\n", 8, 0);

//    if (shutdown(socket_descriptor, 0)) {
//        server_error_handler("Error shutdown socket", Info);
//    }
//    if (shutdown(peer_descriptor, 0)) {
//        server_error_handler("Error shutdown socket", Info);
//    }

    exit(0);
}
