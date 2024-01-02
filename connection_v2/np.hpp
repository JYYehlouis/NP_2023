#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// libaries included: network part
#include "lib.hpp"

int numOfOnlinePlayer;
int numOfPlayinPlayer;

struct infos {
    int sockfd;
    char name[20];
    bool free;
    bool inGame;
};

infos states[LISTENQ];

void * start(void * args) {
    pthread_detach(pthread_self());
    int pos = *(int *) args;
    free(args);

    int c, n;
    c = read(states[pos].sockfd, states[pos].name, sizeof(states[pos].name));
    if ( c <= 0 ) { goto done; }
    printf("Get name: %s\n", states[pos].name);
    n = write(states[pos].sockfd, states[pos].name, strlen(states[pos].name));
    printf("Check!\n");

    fd_set rset, wset;
    char get[MAXLINE], snd[MAXLINE];
    while (1) {
        FD_ZERO(&rset);
        FD_SET(states[pos].sockfd, &rset);

        n = select(states[pos].sockfd + 1, &rset, 0, 0, 0);
        numOfOnlinePlayer = numOfPlayinPlayer = 0;
        for (int i = 0; i < LISTENQ; ++i) {
            if ( states[i].free == false ) { numOfOnlinePlayer += 1; }
            if ( states[i].inGame == true ) { numOfPlayinPlayer += 1; }
        }
        numOfPlayinPlayer = numOfPlayinPlayer / 2;

        if ( n == 0 ) { continue; }
        else if ( n < 0 ) { return(NULL); }
        else {
            if ( FD_ISSET(states[pos].sockfd, &rset) ) {
                read(states[pos].sockfd, get, sizeof(get));
                if ( strcmp(get, REQ_NUM) == 0 ) { 
                    bzero(get, sizeof(get));
                    sprintf(snd, "%d %d", numOfOnlinePlayer, numOfPlayinPlayer); 
                    write(states[pos].sockfd, snd, strlen(snd));
                } else if ( strcmp(get, CLI_CLS) == 0 ) {
                    std::cout << "client close\n";
                    break;
                }
            }
        }
    }

done:
    close(states[pos].sockfd);
    states[pos].free = true;
    states[pos].inGame = false;

    return(NULL);
}
