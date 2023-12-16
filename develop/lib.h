#ifndef _MYPROJ_LIB_
#define _MYPROJ_LIB_

#define SERV_PORT 9877
#define MAXLINE   2048
#define LISTENQ   1024

#define REQUESTID "request id"
#define CHECKID   "check id"
#define WRONGID   "wrong id"
#define NONEXIST  "id not exist"

#define SENDINV   "invitation from id %d"
#define ACCEPTINV "invitation accept from id %d"

// libraries included: basic ones
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sqlite3.h>
#include <pthread.h>

// libaries included: network part
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <sys/select.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/unistd.h>


typedef struct registeredDatas {
    int id;
    char name[100], passwd[100];
    int win, loss, draw;
} data;

int IDs[__INT_MAX__];

void serverInit() {
    memset(IDs, 0, __INT_MAX__);
    IDS[0] = -1;
}


int generateID(int sockfd) {
    int number = rand() % __INT_MAX__;
    while ( IDs[number] ) { number = rand() % __INT_MAX__; }
    IDs[number] = 1;
    return number;
}

/*
    The following functions are for the database.
*/

// -1 means error, and 0 means success
int openDB(sqlite3 **DB) { 
    sqlite3_open("playerInfo.db", DB); 
    if ( DB ) { return 0; }
    else { return -1; }
}

// return SQLITE_OK means success
unsigned int checkDB(sqlite3 *DB) {
    const char cmd[] = 
    "CREATE TABLE IF NOT EXISTS PlayerTable (id INT, username TEXT, password TEXT, win INT, loss INT, draw INT)";
    return sqlite3_exec(DB, cmd, 0, 0, 0);
}

// return SQLITE_OK means success
unsigned int insertNewInfoDB(sqlite3 *DB, int id, char *name, char *password) {
    char cmd[1000];
    sprintf(cmd, "INSERT INTO PlayerTable (id, username, password, win, loss, draw) VALUES (%d, %s, %s, %d, %d, %d)", id, name, password, 0, 0, 0); 
    return sqlite3_exec(DB, cmd, 0, 0, 0);
}

void closeDB(sqlite3 *DB) { sqlite3_close(DB); }


/*
    The following network functions are for server
*/

void handle_alarm(int signo) {}

/*
    The following network functions are for client
*/

void clientStart(int sockfd) {
    char name[100], password[100], getid[20];
    char send[MAXLINE], get[MAXLINE];
    while (1) {
        int n;
        printf("Name: ");
        while ( ( n = read(STDIN_FILENO, name, sizeof(name)) ) <= 1 ) )  {
            if ( n <= 0 ) {
                printf("Login failed!\n");
                return;
            } else if ( n == 1 ) {
            // '\n' will be deleted, so it means no input
                printf("Wrong Input!\n");
                printf("------------------------------\n");
                printf("Name: ");
            }
        }
        name[n] = 0;

        printf("Password: ");
        while ( ( n = read(STDIN_FILENO, password, sizeof(password)) ) <= 1 ) {
            if ( n <= 0 ) {
                printf("Login failed!\n");
                return;
            } else if ( n == 1 ) {
            // '\n' will be deleted, so it means no input
                printf("Wrong Input!\n");
                printf("------------------------------\n");
                printf("Name: %s\n", name);
                printf("Password: ");
            }
        }
        password[n] = 0;

        printf("Personal ID (If you are new to the game, press -1 to create player info): ");
        while (1) {
            n = read(STDIN_FILENO, getid, sizeof(getid))
            if ( n <= 0 ) {
                printf("Login failed!\n");
                return;
            }
            getid[n] = 0;

            int number = atoi(getid);
            if ( number == 0 || number < -1 ) { // unable to convert
                printf("Wrong Input!\n");
                printf("------------------------------\n");
                printf("Name: %s\n", name);
                printf("Password: %s", password);
                printf("Personal ID: ");
            } else if ( number == -1 ) { 
                printf("You are a new player to this game! Requesting for a unique id ...\n");
                sprintf(send, REQUESTID)
                write(sockfd, send, sizeof(send));
                read(sockfd, getid, sizeof(getid));
                printf("Welcome! Your id: %s\n", getid);
                break;
            } else {
                printf("Checking id ...\n");
                sprintf(send, CHECKID);
                write(sockfd, send, sizeof(send));
                read(sockfd, getid, sizeof(getid));
                if ( getid == WRONGID || getid == NONEXIST ) { 
                    printf("id not match, please check all your information.\n");
                    continue;
                } else {
                    printf("Welcome!\n");
                    break;
                }
            }
        }
    }

    // using Q to leave (TBD): using _getch()
    for (;;) {
    }
}


/*
    The following functions are for ANSI escape sequence
*/

// clear the screen and set cursor to (0, 0) of the screen
void screenRst() {
    printf("\x1B[2J");
    printf("\x1B[H"); 
} 


#endif