#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>


char* client_example() {
    struct sockaddr_in peer = {
            .sin_family = AF_INET,
            .sin_port = htons(7500),
            .sin_addr.s_addr = inet_addr("127.0.0.1"),
    };
    int s;
    int rc;
    char buf[1];

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Error init socket descriptor");
        exit(1);
    }

    rc = connect(s, (struct sockaddr *)&peer, sizeof(peer));
    if (rc) {
        perror("Error init connection");
        exit(1);
    }

    rc = send(s, "1", 1, 0);
    if (rc <= 0) {
        perror("Error sending message");
        exit(1);
    }

    rc = recv(s, buf, 1, 0);
    if (rc <= 0) {
        perror("Error receiving message");
        exit(1);
    }

    return buf;
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
    int buf[1];
    const int connection_number = 5;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Error init socket");
        exit(1);
    }

    rc = bind(s, (struct sockaddr *)&local, sizeof(local));
    if (rc < 0) {
        perror("Error binding socket");
        exit(1);
    }

    rc = listen(s, connection_number);
    if (rc) {
        perror("Error listen socket");
        exit(1);
    }

    s1 = accept(s, NULL, NULL);
    if (s1 < 0) {
        perror("Error accept request");
        exit(1);
    }

    rc = recv(s1, buf, 1, 0);
    if (rc <= 0) {
        perror("Error receiving message");
    }

    rc = send(s1, "2", 1, 0);
    if (rc <= 0) {
        perror("Error sending message");
    }

    return buf;
}


int main() {
    server_example();
    return 0;
}
