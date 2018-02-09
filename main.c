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


char* server_example() {
    struct sockaddr_in local = {
            .sin_family = AF_INET,
            .sin_port = htons(7500),
            .sin_addr.s_addr = htonl(INADDR_ANY),
    };
    int s;
    int s1;
    int rc;
    char buf[1];
    const int connection_number = 5;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        server_error_handler("Error init socket", Fatal);
    }

    rc = bind(s, (struct sockaddr *)&local, sizeof(local));
    if (rc < 0) {
        server_error_handler("Error binding socket", Fatal);
    }

    rc = listen(s, connection_number);
    if (rc) {
        server_error_handler("Error listen socket", Fatal);
    }

    s1 = accept(s, NULL, NULL);
    if (s1 < 0) {
        server_error_handler("Error accept request", Fatal);
    }

    rc = recv(s1, buf, 1, 0);
    if (rc <= 0) {
        server_error_handler("Error receiving message", Info);
    }

    rc = send(s1, "2", 1, 0);
    if (rc <= 0) {
        server_error_handler("Error sending message", Info);
    }

    return buf;
}


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
