#ifndef SOCKETS_READ_H
#define SOCKETS_READ_H


#include <stdlib.h>


int readn(int socket_descriptor, char* buf, size_t len);

int readvrec(int socket_descriptor, char* buf, size_t len);


#endif //SOCKETS_READ_H
