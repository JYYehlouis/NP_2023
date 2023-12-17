#include <SFML/Graphics.hpp>
#include "lib_v2.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

// const int boardSize = 15;
// const int tileSize = 30;
// const int windowSize = boardSize * tileSize;
// const int margin = 40;  
// const int chatLogWidth = 200;
// const int chatLogHeight = 300;

// sf::RenderWindow window(sf::VideoMode(windowSize + 5 * margin + chatLogWidth, windowSize + 2.5 * margin), "np_FP_Gomoku");

// enum class Player { None, Player1, Player2 };
// Player currentPlayer = Player::Player1;

// std::string player1Name = "Player 1";
// std::string player2Name = "Player 2";
// int turnCount = 1;

// sf::Texture woodTexture;  
// sf::Font font;

// struct ChatMessage {
//     std::string sender;
//     std::string message;
// };

// std::vector<ChatMessage> chatLog;

// bool loadTextures() {
//     if (!woodTexture.loadFromFile("bg_wood.jpg")) {
//         std::cerr << "Wooden texture loading failed!" << std::endl;
//         return false;
//     }

//     return true;
// }

// void drawBackground(sf::RenderWindow &window) {
//     sf::RectangleShape background(sf::Vector2f(windowSize + 5 * margin + chatLogWidth, windowSize + 2.5 * margin));

//     if (woodTexture.getSize().x > 0 && woodTexture.getSize().y > 0) {
//         background.setTexture(&woodTexture);
//     } else {
//         std::cerr << "Invalid wooden texture size!" << std::endl;
//     }

//     window.draw(background);
// }

// void drawBoard(sf::RenderWindow &window) {
//     for (int i = 0; i < boardSize; ++i) {
//         for (int j = 0; j < boardSize; ++j) {
//             sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
//             tile.setPosition(margin + i * tileSize, margin + j * tileSize);
//             tile.setFillColor(sf::Color(225, 225, 225));
//             tile.setOutlineThickness(3);
//             tile.setOutlineColor(sf::Color(200, 150, 150));
//             window.draw(tile);
//         }
//     }
// }

// void drawUI(sf::RenderWindow &window) {
//     sf::Font font;
//     if (!font.loadFromFile("Silkscreen-Regular.ttf")) {
//         std::cerr << "Font loading failed!" << std::endl;
//         return;
//     }

//     // Draw player names
//     sf::Text player1Text(player1Name, font, 25);
//     player1Text.setPosition(margin, margin - 40);  
//     player1Text.setFillColor(sf::Color::Green);  
//     window.draw(player1Text);

//     sf::Text player2Text(player2Name, font, 25);
//     player2Text.setPosition(windowSize + margin - player2Text.getLocalBounds().width, margin - 40);  
//     player2Text.setFillColor(sf::Color::Red);  
//     window.draw(player2Text);

//     // Draw turn count
//     sf::Text turnCountText("Turn: " + std::to_string(turnCount), font, 20);
//     turnCountText.setPosition(windowSize + margin - turnCountText.getLocalBounds().width, windowSize + margin);
//     window.draw(turnCountText);
    
//     // Draw chat log frame
//     sf::RectangleShape chatLogFrame(sf::Vector2f(chatLogWidth, chatLogHeight));
//     chatLogFrame.setPosition(windowSize + 2 * margin, 2 * margin);
//     chatLogFrame.setFillColor(sf::Color(225, 225, 225));
//     chatLogFrame.setOutlineThickness(2.5);
//     chatLogFrame.setOutlineColor(sf::Color(200, 150, 150));
//     window.draw(chatLogFrame);
    
//     // Draw chat log
//     sf::Text chatTitle("Chat Log:", font, 20);
//     chatTitle.setPosition(windowSize + margin * 2, margin);  
//     window.draw(chatTitle);

//     for (size_t i = 0; i < chatLog.size(); ++i) {
//         sf::Text messageText(chatLog[i].sender + ": " + chatLog[i].message, font, 16);
//         messageText.setPosition(windowSize + margin * 2, margin + 30 + i * 20);  
//         window.draw(messageText);
//     }
// }

// /*
// void handleInput() {
//     sf::Event event;
//     while (window.pollEvent(event)) {
//         if (event.type == sf::Event::Closed) {
//             window.close();
//         }

//         if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            
//             currentPlayer = (currentPlayer == Player::Player1) ? Player::Player2 : Player::Player1;
//             turnCount++;
//         }

//         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
//             // Example: Handle chat message input
//             ChatMessage newMessage;
//             newMessage.sender = (currentPlayer == Player::Player1) ? player1Name : player2Name;
//             newMessage.message = "Hello, World!";  
//             chatLog.push_back(newMessage);
//         }
//     }
// }
// */

// int main() {
//     if (!loadTextures()) {
//         return 1; 
//     }

//     window.setFramerateLimit(60);

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }

//             if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                
//                 currentPlayer = (currentPlayer == Player::Player1) ? Player::Player2 : Player::Player1;
//                 turnCount++;
//             }
//         }
// 	// handleInput();  
        
	
//         window.clear();

//         drawBackground(window);  
//         drawBoard(window);
//         drawUI(window);

//         window.display();
//     }

//     return 0;
// }

int main() {
    startupWindowShow();
    playWindowShow();
}