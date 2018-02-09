#include "init.h"

#include "../pkg/errors.h"

#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
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


struct InitParams parse_args(int argc, char** args) {
    int default_port = 9000;
    const unsigned int default_connection_number = 5;
    int port;

    if (argc > 2) {
        server_error_handler("Expected 1 para: port", Fatal);
    } else if (argc == 2) {
        port = atoi(args[0]);
    } else {
        port = default_port;
    }


    struct InitParams params = {
            .port = default_port,
            .connection_number = default_connection_number,
    };
    return params;
}



struct sockaddr_in init_address(int port) {
    struct sockaddr_in address = {
            .sin_family = AF_INET,
            .sin_port = htons(port),
            .sin_addr.s_addr = htonl(INADDR_ANY),
    };
    return address;
}


int init_socket(struct sockaddr* address, unsigned int connection_number) {
    int socket_descriptor;
    int on;
    int r;

    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    r = bind(socket_descriptor, address, sizeof(*address));
    if(r) {
        server_error_handler("Error binding socket", Fatal);
    }

    r = listen(socket_descriptor, connection_number);
    if (r) {
        server_error_handler("Error listen socket", Fatal);
    }

    return socket_descriptor;
}
