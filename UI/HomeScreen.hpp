#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <string>

class HomeScreen {
public:
    HomeScreen();

    void run();

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
 
 
    bool loadTextures();
    
    void drawBackground();
    
    void drawUI();

    void handleInput();
    

    
};

