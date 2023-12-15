#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sqlite3.h>
// or use log (may be slower)

// Network libraries
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/signal.h>

// MY LIB
#include "lib.h"

void handle_alarm(int signo) {}

/*
    closeDB(database);
    if ( openDB(&database) == -1 || checkDB(database) != SQLITE_OK ) {
        printf("Database Error!\n");
        return 0;
    }
*/

void * gameLogin(void * arg) {
    // get connfd
    int connfd = *(int *) arg;
    free(arg);
    // read username


    // start doing
}

int main() {
    int listenfd, listenFlags, connfd;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;

    // listen file descriptor
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    listenFlags = fcntl(listenfd, F_GETFL);
    if ( fcntl(listenfd, F_SETFL, listenFlags | O_NONBLOCK) == -1 ) {
        printf("fcntl error!\n");
        return 0;
    }

    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);
    bind(listenfd, (struct sockaddr_in *) &servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);

    int *communfd, *id;
    char get[MAXLINE];
    sqlite3 *database;
    pthread_t *singleThread;    
    signal(SIGALRM, handle_alarm);
    serverInit();
    while ( 1 ) {
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

        // id number will be the valid way to check if you are the owner to the account
        id = (int *)malloc(sizeof(int));
        *id = generateID();
        // connfd number        
        communfd = (int *)malloc(sizeof(int));
        *communfd = connfd;
        // Once press submit, the data will be sent

        singleThread = (pthread_t *)malloc(sizeof(pthread_t));
        pthread_create(singleThread, 0, gameLogin, (void *) communfd);    
    }

    return 0;
}
