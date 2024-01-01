#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "np.cpp"

class Gomoku {
public:
    Gomoku();

    void run();

private:
    enum class Player { None, Player1, Player2 };

    sf::RenderWindow window;
    sf::Texture woodTexture;
    sf::Font font;

    const int boardIndex;
    const int tileLen;
    const int boardLen;
    const int margin;
    const int chatLogWidth;
    const int chatLogHeight;
    const int buttonWidth;
    const int buttonHeight;
    int chatLogScrollOffset;
    const int maxVisibleMessages;

    Player board[15][15];
    Player currentPlayer;
    std::string player1Name;
    std::string player2Name;
    int turnCount;
    
    struct ChatMessage {
        std::string sender;
        std::string message;
    };
    std::vector<ChatMessage> chatLog;

    bool loadTextures();

    void drawBackground();

    void drawBoard();

    void drawUI();

    void handleInput();
};


