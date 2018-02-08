#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>


void server_error_handler(char* message, int fatal) {
    perror(message);

    if (fatal) {
        exit(1);
    }
}

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
        server_error_handler("Error init socket", 1);
    }

    rc = bind(s, (struct sockaddr *)&local, sizeof(local));
    if (rc < 0) {
        server_error_handler("Error binding socket", 1);
    }

    rc = listen(s, connection_number);
    if (rc) {
        server_error_handler("Error listen socket", 1);
    }

    s1 = accept(s, NULL, NULL);
    if (s1 < 0) {
        server_error_handler("Error accept request", 1);
    }

    rc = recv(s1, buf, 1, 0);
    if (rc <= 0) {
        server_error_handler("Error receiving message", 0);
    }

    rc = send(s1, "2", 1, 0);
    if (rc <= 0) {
        server_error_handler("Error sending message", 0);
    }

    return buf;
}


int main() {
    server_example();
    return 0;
}
