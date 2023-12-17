#ifndef _PROJ_LIB_TPP_
#define _PROJ_LIB_TPP_

#include "lib_v2.hpp"

/*
 * Functions below can be reused
**/

bool loadTextures(std::string path) {
    if ( textures.loadFromFile(path) == false ) {
        std::cerr << "texture at " << path << " loaded failed.\n";
        return false;
    }
    return true;
}

void drawBackground(sf::RenderWindow &window) {
    sf::RectangleShape bg(sf::Vector2f(window.getSize()));
    bg.setTexture(&textures);
    window.draw(bg);
}

/*
 * Functions below are for the start menu  
**/

void startupWindowShow() {
    window = new sf::RenderWindow(sf::VideoMode(startWidth, startHeight), "Login");
    if ( loadTextures("../src/textures/bg_start.png") == false ) { exit(0); }

    while ( (*window).isOpen() == true ) {
        while ( (*window).pollEvent(event) ) {
            switch ( event.type ) {
                case sf::Event::Closed:
                    (*window).close();
                    break;
                default:
                    continue;
            }
        }

        (*window).clear();
        drawBackground(*window);
        (*window).display();
    }
    delete window;
}

/*
 * Functions below are for the playing design
**/

void drawBoard(sf::RenderWindow &window) {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(margin + i * tileSize, margin + j * tileSize);
            tile.setFillColor(sf::Color(225, 225, 225));
            tile.setOutlineThickness(3);
            tile.setOutlineColor(sf::Color(200, 150, 150));
            window.draw(tile);
        }
    }
}

void drawUI(sf::RenderWindow &window) {
    sf::Font font;
    if (!font.loadFromFile("Silkscreen-Regular.ttf")) {
        std::cerr << "Font loading failed!" << std::endl;
        return;
    }

    // Draw player names
    sf::Text player1Text(player1Name, font, 25);
    player1Text.setPosition(margin, margin - 40);  
    player1Text.setFillColor(sf::Color::Green);  
    window.draw(player1Text);

    sf::Text player2Text(player2Name, font, 25);
    player2Text.setPosition(windowSize + margin - player2Text.getLocalBounds().width, margin - 40);  
    player2Text.setFillColor(sf::Color::Red);  
    window.draw(player2Text);

    // Draw turn count
    sf::Text turnCountText("Turn: " + std::to_string(turnCount), font, 20);
    turnCountText.setPosition(windowSize + margin - turnCountText.getLocalBounds().width, windowSize + margin);
    window.draw(turnCountText);
    
    // Draw chat log frame
    sf::RectangleShape chatLogFrame(sf::Vector2f(chatLogWidth, chatLogHeight));
    chatLogFrame.setPosition(windowSize + 2 * margin, 2 * margin);
    chatLogFrame.setFillColor(sf::Color(225, 225, 225));
    chatLogFrame.setOutlineThickness(2.5);
    chatLogFrame.setOutlineColor(sf::Color(200, 150, 150));
    window.draw(chatLogFrame);
    
    // Draw chat log
    sf::Text chatTitle("Chat Log:", font, 20);
    chatTitle.setPosition(windowSize + margin * 2, margin);  
    window.draw(chatTitle);

    for (size_t i = 0; i < chatLog.size(); ++i) {
        sf::Text messageText(chatLog[i].sender + ": " + chatLog[i].message, font, 16);
        messageText.setPosition(windowSize + margin * 2, margin + 30 + i * 20);  
        window.draw(messageText);
    }
}

void playWindowShow() {
    window = new sf::RenderWindow(sf::VideoMode(playWidth, playHeight), "Gomoku");
    if ( loadTextures("../src/textures/bg_wood.jpg") == false ) { exit(0); }

    while ( (*window).isOpen() == true ) {
        sf::Event event;
        while ( (*window).pollEvent(event) == true ) {
            switch ( event.type ) {
                case sf::Event::Closed:
                    (*window).close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if ( event.mouseButton.button == sf::Mouse::Left ) {
                        currentPlayer = (currentPlayer == Player::Player1) ? Player::Player2 : Player::Player1;
                        turnCount++;
                    }
            }
        } 
        
	
        (*window).clear();

        drawBackground(*window);  
        drawBoard(*window);
        drawUI(*window);

        (*window).display();
    }
    delete window;
}

#endif
