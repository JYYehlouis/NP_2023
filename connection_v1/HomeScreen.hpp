#pragma once

#include "lib.hpp"

class HomeScreen {
public:
    HomeScreen();

    void run();

    void init(char *addr);

private:
    sf::RenderWindow window;
    sf::Texture woodTexture;
    sf::Font font;
    sf::Text onlinePlayerCount;
    sf::Text inGamePlayerCount;
    sf::RectangleShape okButton;
    sf::Text playerNameText;
    sf::Text helloPlayerText;
    sf::RectangleShape readyButton;
    
    const int margin;
    const int subMargin;
    bool nameEntered;  // Flag to track whether the player has entered a name
    bool isReady;
    int onlinePlayerNum;
    int inGamePlayerNum;

    // ---
    int sockfd;
    bool connection;
    struct sockaddr_in servaddr;
    // ---
 
    bool loadTextures();
    
    void drawBackground();
    
    void drawUI();

    void handleInput();

    
};

