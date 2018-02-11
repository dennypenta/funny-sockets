#include <stdio.h>
#include <stdlib.h>

#include "errors.h"


int is_fatal(enum ErrorMode mode) {
    return mode == Fatal;
}

void fatal_error_handler(int code) {
    exit(code);
}


void server_error_handler(char* message, enum ErrorMode mode) {
    perror(message);

    if (is_fatal(mode)) {
        fatal_error_handler(1);
    }
}
