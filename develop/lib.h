#ifndef _MYPROJ_LIB_
#define _MYPROJ_LIB_

#define SERV_PORT 9877
#define MAXLINE   2048
#define LISTENQ   1024

#include <memory.h>

struct registeredDatas {
    char name[100];
};

int IDs[__INT_MAX__];

void serverInit() {
    memset(IDs, 0, __INT_MAX__);
}

#include <stdlib.h>

int generateID() {
    int number = rand() % __INT_MAX__;
    while ( IDs[number] ) { number = rand() % __INT_MAX__; }
    IDs[number] = 1;
    return number;
}

/*
    The following functions are for the database.
*/

#include <sqlite3.h>
// -1 means error, and 0 means success
int openDB(sqlite3 **DB) { 
    sqlite3_open("playerInfo.db", DB); 
    if ( DB ) { return 0; }
    else { return -1; }
}

unsigned int checkDB(sqlite3 *DB) {
    const char cmd[] = 
    "CREATE TABLE IF NOT EXISTS PlayerTable (username TEXT, password TEXT, win INT, loss INT, draw INT)";
    return sqlite3_exec(DB, cmd, 0, 0, 0);
}

void closeDB(sqlite3 *DB) { sqlite3_close(DB); }


/*
    The following functions are for
*/

#endif