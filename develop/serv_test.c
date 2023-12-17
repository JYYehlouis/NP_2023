#include "lib.h"

int main() {
    int listenfd, listenFlags, connfd;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    listenFlags = fcntl(listenfd, F_GETFL);
    fcntl(listenfd, F_SETFL, listenFlags | O_NONBLOCK);
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listen, LISTENQ);

    signal(SIGALRM, handle_alarm);
    for (;;) {
        clilen = sizeof(cliaddr);
        alarm(5);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        if ( connfd == -1 && errno != EWOULDBLOCK ) { 
            printf("Unexpected Error!\n");
            break; 
        } else {
            alarm(0);
            if ( errno == EWOULDBLOCK ) { continue; }
        }
    }

    return 0;
}