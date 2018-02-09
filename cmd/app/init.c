#include "init.h"

#include "../../pkg/errors.h"

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


static void set_address(char* hname, char* sname, struct sockaddr_in *sap, char* protocol) {
    struct servent *sp;
    struct hostent *hp;
    char* endptr;
    short port;

    char* err_msg;

    bzero(sap, sizeof(*sap));
    sap->sin_family = AF_INET;
    if (hname != NULL && !inet_aton(hname, &sap->sin_addr)) {
        hp = gethostbyname(hname);
        if (hp == NULL) {
            sprintf(err_msg, "Unknown host %s\n", hname);
            server_error_handler(err_msg, Fatal);
        }

        sap->sin_addr = *(struct in_addr*)hp->h_addr;
    } else {
        sap->sin_addr.s_addr = htonl(INADDR_ANY);
    }

    port = strtol(sname, &endptr, 0);

    if (*endptr == '\0') {
        sap->sin_port = htons(port);
    } else {
        sp = getservbyname(sname, protocol);
        if(sp == NULL) {
            sprintf(err_msg, "Unknown service %s\n", sname);
            server_error_handler(err_msg, Fatal);
        }

        sap->sin_port = sp->s_port;
    }
}


void run(int argc, char** argv) {
    const int on = 1;
    const short connection_number = 5;

    struct sockaddr_in local;
    struct sockaddr_in peer;
    char* hname;
    char* sname;
    int peerlen;
    int s1;
    int s;

    // init

    if (argc == 2) {
        hname = NULL;
        sname = argv[1];
    } else {
        hname = argv[1];
        sname = argv[2];
    }

    set_address(hname, sname, &local, "tcp");
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        server_error_handler("Error init socket", Fatal);
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) {
        server_error_handler("Error set socket options", Fatal);
    }

    if(bind(s, (struct sockaddr*)&local, sizeof(local))) {
        server_error_handler("Error binding socket", Fatal);
    }

    if (listen(s, connection_number)) {
        server_error_handler("Error listen socket", Fatal);
    }

    peerlen = sizeof(peer);
    s1 = accept(s, (struct sockaddr*)&peer, &peerlen);
    if (s1 < 0) {
        server_error_handler("Error accept request", Info);
    }

    send(s1, "hello", 4, 0);

    exit(0);
}
