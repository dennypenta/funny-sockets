#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#define MAXLINE 4096
#define LISTEN_QUEUE 5

void sig_child(int signo) {
    pid_t pid;
    int stat;

    while (1) {
        pid = waitpid(-1, &stat, WNOHANG);
        if (pid < 1) {
            break;
        }
    }
}


int main(int argc, char **argv) {
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;
    int child_pid;
    int r;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("Error while initializing socket");
        exit(listenfd);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(13);	/* daytime server */

    r = bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
    if (r < 0) {
        perror("Error while binding socket");
        exit(r);
    }

    r = listen(listenfd, LISTEN_QUEUE);
    if (r < 0) {
        perror("Error while listening socket");
        exit(r);
    }
    signal(SIGCHLD, sig_child);

    for ( ; ; ) {
        connfd = accept(listenfd, (struct sockaddr*) NULL, NULL);
        if (connfd < 0) {
            if (errno == EINTR) {
                continue;
            }
            perror("Error while accepting socket");
            exit(connfd);
        }

        child_pid = fork();
        if (child_pid == 0) {
            ticks = time(NULL);
            snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
            r = write(connfd, &buff, sizeof(buff));
            if (r < 0) {
                perror("Error while writing socket");
                exit(connfd);
            }

            close(listenfd);
            exit(0);
        }

        close(connfd);
    }
}
