#ifndef _PROJ_LIB_HPP_
#define _PROJ_LIB_HPP_

#include <iostream>

#include <SFML/Graphics.hpp>

/*
 * \brief A variable for loading textures
**/
sf::RenderWindow *window;
sf::Texture textures;
sf::Event event;

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
void drawBackground(sf::RenderWindow &window);

/*
 * Functions below are for the start menu  
**/

const int startWidth = 400, startHeight = 500;
// sf::RenderWindow startWindow(sf::VideoMode(startWidth, startHeight), "Login");
    /*
     * \brief This is a function that shows the startup window.
    **/
void startupWindowShow();

// Designation of the start menu of two textboxes and one button

#include <vector>

/*
 * Functions below are for the playing design
**/

    /*
     * \param window draw a board on current window
    **/
void drawBoard(sf::RenderWindow &window);

    /*
     * \param window write informations on current window
    **/
void drawUI(sf::RenderWindow &window);

const int boardSize = 15;
const int tileSize = 30;
const int windowSize = boardSize * tileSize;
const int margin = 40;  
const int chatLogWidth = 200;
const int chatLogHeight = 300;
const int playWidth = windowSize + 5 * margin + chatLogWidth;
const int playHeight = windowSize + 2.5 * margin;

// sf::RenderWindow playWindow(sf::VideoMode(, ), "np_FP_Gomoku");

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