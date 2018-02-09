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

static void set_address(char* port, struct sockaddr_in *sap, char* protocol) {
    struct servent *sp;
    struct hostent *hp;
    char* endptr;
    short int_port;

    bzero(sap, sizeof(*sap));
    sap->sin_family = AF_INET;
}


int main(int argc, char** argv) {
    int port;

    if (argc > 2) {
        server_error_handler("Expected 1 para: port", Fatal);
    } else if (argc == 2) {
        port = atoi(argv[0]);
    } else {
        port = 9000;
    }

    printf("Port: %i\n", port);
}
