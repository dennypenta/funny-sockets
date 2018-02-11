#ifndef SOCKETS_ERRORS_H
#define SOCKETS_ERRORS_H


enum ErrorMode {
    Info = 0,
    Fatal = 1,
};


void server_error_handler(char*, enum ErrorMode);


#endif //SOCKETS_ERRORS_H
