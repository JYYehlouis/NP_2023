#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <sys/select.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/unistd.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>
#include <string>

#include <cstring>
#include <cstdlib>
#include <cstdio>

#define LISTENQ   1024
#define MAXLINE   4096
#define SERV_PORT 9877

#define REQ_NUM "INFO_OF_NUMBERS"
#define CLI_CLS "CLI_CLOSED"

