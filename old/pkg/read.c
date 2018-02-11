#include <sys/socket.h>
#include <errno.h>

#include "read.h"


int read_error(int code) {
    if (code < 0) {
        return -1;
    }

    return 0;
};


int readn(int socket_descriptor, char* buf, size_t len) {
    int rc;
    int count = len;

    while(count > 0) {
        rc = recv(socket_descriptor, buf, count, 0);
        if (rc < 0) {
            if (errno == EINTR) {
                continue;
            }

            return -1;
        }

        if (rc == 0) {
            return len - count;
        }

        buf += rc;
        count -= rc;
    }

    return len;
}

int readvrec(int socket_descriptor, char* buf, size_t len) {
    unsigned int reclen;
    int rc;

    rc = readn(socket_descriptor, reclen, sizeof(unsigned int));
    if (rc != sizeof(unsigned int)) {
        return read_error(rc);
    }

    reclen = htonl(reclen);
    if (reclen > len) {
        while (reclen > 0) {
            rc = readn(socket_descriptor, buf, len);
            if (rc != len) {
                return read_error(rc);
            }

            reclen -= len;
            if (reclen < len) {
                len = reclen;
            }
        }

        errno = EMSGSIZE;
        return -1;
    }

    rc = readn(socket_descriptor, buf, reclen);
    if (rc != reclen) {
        return read_error(rc);
    }

    return rc;
}
