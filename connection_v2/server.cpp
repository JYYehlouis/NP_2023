#include "np.hpp"
using namespace std;

int main() {
    int listenfd, flags, connfd;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;

    numOfOnlinePlayer = numOfPlayinPlayer = 0;
    for (int i = 0; i < LISTENQ; ++i) { 
        states[i].free = true; 
        states[i].inGame = false;
    }

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);

    int *args;
    pthread_t *p;
    for (;;) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        // if connection established
        args = (int *)malloc(sizeof(int));
        for (int i = 0; i < LISTENQ; ++i) {
            if ( states[i].free ) {
                *args = i;
                states[i].free = false;
                states[i].sockfd = connfd;
                break;
            }
        }

        p = (pthread_t *)malloc(sizeof(pthread_t));
        pthread_create(p, 0, start, (void *) args);
    }

    return 0;
}