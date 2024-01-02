#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>

const int boardIndex = 15; // Index of the board, which is 15 * 15 (row * column).
const int tileLen = 30; // Length of a board tile.
const int boardLen = (boardIndex - 1) * tileLen; // Length of the board.
const int margin = 40;  // Window margin.
const int chatLogWidth = 250; //Width of the chatlog.
const int chatLogHeight = 300; // Height of the chatlog.
const int buttonWidth = 37.5; // Width of the button.
const int buttonHeight = 30; // Height of the button.
int chatLogScrollOffset = 0;
const int maxVisibleMessages = (chatLogHeight - 30) / 20; // For scrollable chatlog. 

// Player class: none -> for initialization of board, 1 -> player 1, 2 -> player 2. 
// Each tile on the board is initially set to player none; the current player is initially set to player 1.
// The information of board and current player needs to be updated by client.
// When current player != /playerName, /playerName cannot send board information to the other client.
enum class Player { None, Player1, Player2 };
Player board[boardIndex][boardIndex] = {Player::None}; 
Player currentPlayer = Player::Player1;

/*--------------------------------------------*/
std::string player1Name = "Player 1"; // Place holder for name of player 1, should be changed when combined with tcp client.
std::string player2Name = "Player 2"; // Place holder for name of player 2, should be changed when combined with tcp client.
/*--------------------------------------------*/

// Recording current turn count.
// The information of turn count needs to be updated by client.
int turnCount = 1;

// Chat log structure: Each message is shown in the form of -> (Sender: message).
struct ChatMessage {
    std::string sender;
    std::string message;
};
std::vector<ChatMessage> chatLog; // Vector of chat messages.


// Background and font textures.
sf::Texture woodTexture;  
sf::Font font;
// Function: Load textures. Returns true if success, otherwise returns false.
bool loadTextures() {
    if (!woodTexture.loadFromFile("bg_wood.jpg")) {
        std::cout << "Background texture loading failed!" << std::endl;
        return false;
    }
    
    if (!font.loadFromFile("Silkscreen/Silkscreen-Regular.ttf")) {
        std::cout << "Font loading failed!" << std::endl;
        return false;
    }
    return true;
}

// Size of the rendering game window.
sf::RenderWindow window(sf::VideoMode(boardLen + 4 * margin + chatLogWidth, boardLen + 3 * margin), "np_FP_Gomoku");

//Fuction: Draw background. Background size must be larger than 0, and should be at least the same as window size.
void drawBackground(sf::RenderWindow &window) {
    sf::RectangleShape background(sf::Vector2f(boardLen + 4 * margin + chatLogWidth, boardLen + 3 * margin));
    if (woodTexture.getSize().x > 0 && woodTexture.getSize().y > 0) {
        background.setTexture(&woodTexture);
    } else {
        std::cout << "Invalid wooden texture size!" << std::endl;
    }
    window.draw(background);
}

//Function: Draw board. This should be updated from both clients' actions.
void drawBoard(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // Get mouse response.
    sf::RectangleShape boardBackground(sf::Vector2f((boardIndex - 1) * tileLen, (boardIndex - 1) * tileLen)); // Board background size should be 14 tiles * 14 tiles.
    boardBackground.setPosition(margin+ tileLen / 8, margin+ tileLen / 8); // Set position: margin + offset of leftmost tile (tileLen / 8).
    boardBackground.setFillColor(sf::Color(200, 200, 200));
    window.draw(boardBackground);
    
    for (int i = 0; i < boardIndex; ++ i) {
    	sf::RectangleShape line(sf::Vector2f((boardIndex - 1) * tileLen, 2)); // Horizontal line.
        line.setPosition(margin, margin + i * tileLen + tileLen / 8);
        line.setFillColor(sf::Color(200, 75, 75));
        window.draw(line);
    }
    for (int i = 0; i < boardIndex; ++ i) {
    	sf::RectangleShape line(sf::Vector2f(2, (boardIndex - 1) * tileLen)); // Vertical line.
        line.setPosition(margin + i * tileLen + tileLen / 8, margin);
        line.setFillColor(sf::Color(200, 75, 75));
        window.draw(line);
    }
    
    for (int i = 0; i < boardIndex; ++ i) {
        for (int j = 0; j < boardIndex; ++ j) {
            if (i == 7 && j == 7) { // Emphasize the size of the middle dot.
            	sf::RectangleShape dot(sf::Vector2f(tileLen / 2.75, tileLen / 2.75));
            	dot.setPosition(margin + j * tileLen - tileLen / 16, margin + i * tileLen - tileLen / 16);  // Offset of width and height = tileLen / 16.
            	// Changes color if mouse hovers over it.
            	if (dot.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            	    dot.setFillColor(sf::Color(100, 100, 150));
        	} else {
            	    dot.setFillColor(sf::Color(150, 100, 100));
        	}
            	dot.setOutlineThickness(0); // No outlines.
            	window.draw(dot);	
            }
	    else {
	    	sf::RectangleShape dot(sf::Vector2f(tileLen / 4, tileLen / 4));
            	dot.setPosition(margin + j * tileLen, margin + i * tileLen);  
            	if (dot.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            	    dot.setFillColor(sf::Color(100, 150, 150));
        	} else {
            	    dot.setFillColor(sf::Color(150, 100, 100));
        	}
            	dot.setOutlineThickness(0);
            	window.draw(dot);
	    }
	    
            // Draw symbol (o or x) on top of the dot
            sf::Text symbolText;
            symbolText.setFont(font);
            symbolText.setCharacterSize(24);
            symbolText.setFillColor(sf::Color(0, 0, 0));
            
            if (board[j][i] == Player::Player1) {
                symbolText.setString("X");
                symbolText.setFillColor(sf::Color(0, 0, 0));
            } else if (board[j][i] == Player::Player2) {
                symbolText.setString("O");
                symbolText.setFillColor(sf::Color(255, 255, 255));
            }

            symbolText.setPosition(margin + j * tileLen - tileLen / 4, margin + i * tileLen - tileLen / 2); // Offset of width = tileLen / 4, offset of height = tileLen / 2.
            window.draw(symbolText);
        }
    }
}

void drawUI(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    
    // Draw player names
    sf::Text player1Text(player1Name, font, 24);
    player1Text.setPosition(margin, margin / 8);  
    player1Text.setFillColor(sf::Color(0, 128, 0));  
    window.draw(player1Text);
    
    sf::Text player2Text(player2Name, font, 24);
    player2Text.setPosition(boardLen + margin - player2Text.getLocalBounds().width, margin / 8);  
    player2Text.setFillColor(sf::Color(128, 0, 0));  
    window.draw(player2Text);

    // Draw turn count
    sf::Text turnCountText("Turn: " + std::to_string(turnCount) + "(" + ((currentPlayer == Player::Player1) ? player1Name : player2Name) + ")", font, 24);
    turnCountText.setPosition(boardLen + margin - turnCountText.getLocalBounds().width, boardLen + margin + margin / 2);
    window.draw(turnCountText);
    
    // Draw chat log frame
    sf::RectangleShape chatLogFrame(sf::Vector2f(chatLogWidth, chatLogHeight));
    chatLogFrame.setPosition(margin + boardLen + 1.5 * margin, 2 * margin);
    chatLogFrame.setFillColor(sf::Color(225, 225, 225));
    chatLogFrame.setOutlineThickness(2.5);
    chatLogFrame.setOutlineColor(sf::Color(200, 150, 150));
    window.draw(chatLogFrame);
    
    // Draw chat log within the frame
    sf::View chatLogView(sf::FloatRect(0, 0, chatLogWidth, chatLogHeight));
    chatLogView.setViewport(sf::FloatRect((float)(margin + boardLen + 1.5 * margin) / window.getSize().x, (float)(2 * margin) / window.getSize().y, (float)chatLogWidth / window.getSize().x, (float)chatLogHeight / window.getSize().y));
    window.setView(chatLogView);

    sf::Text chatTitle("Chat Log:", font, 20);
    chatTitle.setPosition(margin / 5, 0);
    window.draw(chatTitle);

    size_t startIndex = (chatLog.size() > maxVisibleMessages) ? chatLog.size() - maxVisibleMessages : 0; // Place to show chat (for scrolling purpose).

    // Actually draw each chatlog.
    for (size_t i = startIndex; i < startIndex + maxVisibleMessages; ++ i) {
        if (i < chatLog.size()) { 
            sf::Text messageText(chatLog[i].sender + ": " + chatLog[i].message, font, 16);
            if (chatLog[i].sender == player1Name) {
                messageText.setFillColor(sf::Color(0, 128, 0));
            } 
            else if (chatLog[i].sender == player2Name) {
                messageText.setFillColor(sf::Color(128, 0, 0));
            }
            messageText.setPosition(margin / 5, 30 + (i - startIndex) * 20); // Scrollable chat.
            window.draw(messageText);
        }
    }

    // Reset the view to the default view
    window.setView(window.getDefaultView());
    // Draw buttons
    for (int i = 0; i < 4; ++ i) {
        sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
        button.setPosition(boardLen + 2.5 * margin + i * (chatLogWidth / 4) + 10, chatLogHeight + 2.5 * margin);
        // Change button color if mouse hovers over it.
        if (button.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            button.setFillColor(sf::Color(100, 100, 255));
        } else {
            button.setFillColor(sf::Color(200, 200, 200));
        }
        button.setOutlineThickness(2);
        button.setOutlineColor(sf::Color(100, 100, 100));
        window.draw(button);
        
        // Draw text inside each button based on the button index
        sf::Text buttonText;
        buttonText.setFont(font);
        buttonText.setCharacterSize(18);
        buttonText.setFillColor(sf::Color(0, 0, 0));

        if (button.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            buttonText.setFillColor(sf::Color(255, 255, 255));
        } else {
            buttonText.setFillColor(sf::Color(0, 0, 0));
        }

        switch (i) {
            case 0:
                buttonText.setString("gg");
                break;
            case 1:
                buttonText.setString("LOL");
                break;
            case 2:
                buttonText.setString(" :)");
                break;
            case 3:
                buttonText.setString(" :(");
                break;
            default:
                break;
        }
        // Center the text inside the button
        sf::FloatRect textBounds = buttonText.getLocalBounds();
        buttonText.setPosition(button.getPosition().x + (buttonWidth - textBounds.width) / 4, button.getPosition().y + (buttonHeight - textBounds.height) / 5);

        window.draw(buttonText);  
    }
}

void handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	    
	    // Check if the mouse is within the board area
            if (mousePosition.x >= margin && mousePosition.x < boardLen + 1.5 * margin &&
                mousePosition.y >= margin && mousePosition.y < boardLen + 1.5 * margin) {
                // Calculate the indices of the clicked tile
                int columnIndex = (mousePosition.y - margin) / tileLen;
                int rowIndex = (mousePosition.x - margin) / tileLen;

                // Calculate the distance from the mouse position to the top left corner of the clicked tile
    		float dx = mousePosition.y - margin - columnIndex * tileLen;
    		float dy = mousePosition.x - margin - rowIndex * tileLen;

    		// Check if the mouse is within the adjusted click registration area
    		if (dx >= -tileLen / 4 && dx <= tileLen / 4 && dy >= -tileLen / 4 && dy <= tileLen / 4) {
        	    // Check if the tile is empty
        	        
        	    /*---------------------------------------------------*/  // Client should send this information to the other client via server.
        	    if (board[rowIndex][columnIndex] == Player::None) {
            	        // Set the player's symbol on the clicked tile.
               	        board[rowIndex][columnIndex] = currentPlayer;

	            	// Update the turn count.
             	        turnCount++;

            	        // Switch to the next player
                        currentPlayer = (currentPlayer == Player::Player1) ? Player::Player2 : Player::Player1;
                    /*---------------------------------------------------*/ 
                    }
    		}
            }
	    
            // Check if the mouse is over a button
            for (int i = 0; i < 4; ++i) {
                sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
                button.setPosition(sf::Vector2f(boardLen + 2.5 * margin + i * (chatLogWidth / 4) + 10, chatLogHeight + 2.5 * margin));


                if (button.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    // Handle button press based on the button index
                    ChatMessage newMessage;
                    newMessage.sender = (currentPlayer == Player::Player1) ? player1Name : player2Name;
                    /*---------------------------------------------------*/ // Client should send this information to the other client via server.
                    switch (i) {
                        case 0:
                            newMessage.message = "gg";
                            break;
                        case 1:
                            newMessage.message = "LOL";
                            break;
                        case 2:
                            newMessage.message = ":)";
                            break;
                        case 3:
                            newMessage.message = ":(";
                            break;
                        default:
                            break;
                    }
                    /*---------------------------------------------------*/ 
                    chatLog.push_back(newMessage);
                    break;  // No need to check other buttons
                }
            }

            
        }
        
        // Handle mouse wheel scrolling for chat log
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                chatLogScrollOffset += static_cast<int>(event.mouseWheelScroll.delta);

                // Ensure that the scroll offset stays within bounds
                if (chatLogScrollOffset < 0) {
                    chatLogScrollOffset = 0;
                } else if (chatLogScrollOffset > static_cast<int>(chatLog.size()) - maxVisibleMessages) {
                    chatLogScrollOffset = static_cast<int>(chatLog.size()) - maxVisibleMessages;
                }
            }
        }
    }
}

int main() {
    if (!loadTextures()) {
        return 1; 
    }

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        handleInput();
        
        
        window.clear();

        drawBackground(window);  
        drawBoard(window);
        drawUI(window);

        window.display();
    }

    return 0;
}

