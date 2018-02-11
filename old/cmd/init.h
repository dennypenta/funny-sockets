#ifndef SOCKETS_INIT_H
#define SOCKETS_INIT_H


#include <sys/socket.h>


struct InitParams {
    int port;
    unsigned int connection_number;
};

struct InitParams parse_args(int argc, char** args);

struct sockaddr_in init_address(int port);

int init_socket(struct sockaddr* address, unsigned int connection_number);


#endif //SOCKETS_INIT_H
