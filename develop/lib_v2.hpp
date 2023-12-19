#ifndef _PROJ_LIB_HPP_
#define _PROJ_LIB_HPP_

#include <iostream>

#include <SFML/Graphics.hpp>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <sys/select.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/unistd.h>

// window management
#define CLOSE   0
#define STARTUP 1
#define LOBBY   2
#define PLAY    3

// start up errors
#define NOERR      0
#define MAXSIZEERR 1
// #define WRONGCH    2

/*
 * \brief A variable for loading textures
**/
sf::RenderWindow *window;
sf::Texture textures;
sf::Event event;

// the font for showing error messages
sf::Font errFont;

/*
 * \brief A variable for window management
**/
int windowManage;

/*
 * \brief A variable for connecting with server
**/
int sockfd;


/*
 * Functions below can be reused
**/

    /*
     * \param path path to the loaded pictures 
    **/
bool loadTextures(std::string path);

    /*
     * \param window current window you want to design 
    **/
void drawBackground(sf::RenderWindow * &window);

    /*
     * \param window current window you want to design
     * \param size the size you want to design (float, float)
     * \param pos the position you want to put (float, float)
    **/
void drawRectangle(sf::RenderWindow * &window, sf::Vector2f size, sf::Vector2f pos);

    /*
     * \param window current window you want to design
     * \param pos the position you want to put (float, float)
     * \param msg the error message you want to show
    **/
void drawErrorMes(sf::RenderWindow * &window, sf::Vector2f pos, sf::String msg);

/*
 * Functions below are for the start menu  
**/

const int startWidth = 600, startHeight = 800;
sf::String startupStr[2]; // up to 24 words
sf::Text startupShowStr[2];
int startflags[2];

    /*
     * \brief This is a function that shows the startup window.
    **/
void startupWindowShow();

    /*
     * \param window the current window you want to design
    **/
void drawInputInfo(sf::RenderWindow * &window);

// Designation of the start menu of two textboxes and one button

/*
 * Functions below are for the lobby design
**/

    /*
     * \brief This is a function that shows the lobby window
    **/
void lobbyWindowShow();

    /*
     * \brief This is a function that provides information of users
    **/
void requestInfo();


#include <vector>

/*
 * Functions below are for the playing design
**/

    /*
     * \param window draw a board on current window
    **/
void drawBoard(sf::RenderWindow * &window);

    /*
     * \param window write informations on current window
    **/
void drawUI(sf::RenderWindow * &window);

const int boardSize = 15;
const int tileSize = 30;
const int windowSize = boardSize * tileSize;
const int margin = 40;  
const int chatLogWidth = 200;
const int chatLogHeight = 300;
const int playWidth = windowSize + 5 * margin + chatLogWidth;
const int playHeight = windowSize + 2.5 * margin;

enum class Player { None, Player1, Player2 };
Player currentPlayer = Player::Player1;

std::string player1Name = "Player 1";
std::string player2Name = "Player 2";
int turnCount = 1;

sf::Texture woodTexture;  
sf::Font font;

struct ChatMessage {
    std::string sender;
    std::string message;
};

std::vector<ChatMessage> chatLog;
    /*
     * \brief This is a function that shows the playing window.
    **/
void playWindowShow();

#include "lib_v2.tpp"

#endif