#include "lib.h"

int main(int argc, char *argv[]) {
    if ( argc != 3 ) { return 0; }
    
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    clientStart(sockfd);

    return 0;
}