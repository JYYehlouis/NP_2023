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

void drawBackground(sf::RenderWindow * &window) {
    sf::RectangleShape bg(sf::Vector2f(window->getSize()));
    bg.setTexture(&textures);
    window->draw(bg);
}

void drawRectangle(sf::RenderWindow * &window, sf::Vector2f size, sf::Vector2f pos) {
    sf::RectangleShape rect(size);
    rect.setPosition(pos);
    rect.setFillColor({204, 204, 204});
    window->draw(rect);
}

void drawErrorMes(sf::RenderWindow * &window, sf::Vector2f pos, sf::String msg) {
    if ( errFont.loadFromFile("../src/fonts/MartianMonoNerdFontMono-Bold.ttf") == false ) {
        std::cerr << "Font loading failed!\n";
        exit(0);
    }

    sf::Text showText;
    showText.setFont(errFont);
    showText.setScale(0.6, 0.6);
    showText.setString(msg);
    showText.setPosition(pos);
    showText.setFillColor(sf::Color::Red);

    window->draw(showText);
}

/*
 * Functions below are for the start menu  
**/

void startupWindowShow() {
    sf::Font font;
    if ( font.loadFromFile("../src/fonts/3270NerdFontMono-Regular.ttf") == false ) { 
        std::cerr << "Font loading failed!\n";
        exit(0); 
    }

    window = new sf::RenderWindow(sf::VideoMode(startWidth, startHeight), "Login");
    if ( loadTextures("../src/textures/bg_start.png") == false ) { exit(0); }

    startupStr[0] = startupStr[1] = "";
    startflags[0] = startflags[1] = NOERR;
    for (int i = 0; i < 2; ++i) {
        startupShowStr[i].setFont(font);
        startupShowStr[i].setFillColor(sf::Color::Black);
        if ( i == 0 ) { startupShowStr[i].setPosition(190, 110); }
        else { startupShowStr[i].setPosition(190, 260); }
    }
    int i = 0;
    while ( window->isOpen() == true ) {
        while ( window->pollEvent(event) ) {
            switch ( event.type ) {
                case sf::Event::Closed: // window close
                    window->close();
                    windowManage = 0;
                    break;
                case sf::Event::TextEntered:
                    if ( event.text.unicode == '\b' ) { 
                        startupStr[i].erase(startupStr[i].getSize() - 1, 1);
                        if ( startflags[i] == MAXSIZEERR ) { startflags[i] = NOERR; } 
                    } else if ( event.text.unicode == '\t' ) { 
                        i++;
                        if ( i == 2 ) { i = i % 2; } 
                    } else if ( ( event.text.unicode >= 'a' && event.text.unicode <= 'z') || 
                                ( event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||
                                ( event.text.unicode >= '0' && event.text.unicode <= '9') ||
                                ( event.text.unicode == '_' ) ) { 
                        if ( startupStr[i].getSize() < 24 ) { startupStr[i] += event.text.unicode; }
                        else { startflags[i] = MAXSIZEERR; }
                    } // else { startflags[i] = WRONGCH; }
                    for (int j = 0; j < 2; ++j) { startupShowStr[j].setString(startupStr[j]); }
                    goto done;
                default:
                    continue;
            }
        }

done:
        window->clear();
        drawBackground(window);
        drawRectangle(window, {400.f, 60.f}, {180.f, 100.f});
        drawRectangle(window, {400.f, 60.f}, {180.f, 250.f});
        for (int j = 0; j < 2; ++j) {
            if ( startflags[j] == MAXSIZEERR ) { drawErrorMes(window, {180.f, 150 * j + 180.f}, "WARNING: At least 24 characters!"); }
            // else if ( startflags[i] == WRONGCH ) { 
            //     drawErrorMes(window, {160.f, 180.f}, "WARNING: Unexpected Input!"); 
            //     startflags[i] = NOERR;
            // }
            drawInputInfo(window);
            window->draw(startupShowStr[j]);
        }
        window->display();
    }
    delete window;
}

void drawInputInfo(sf::RenderWindow * &window) {
    sf::Font font;
    if ( font.loadFromFile("../src/fonts/3270NerdFontMono-Regular.ttf") == false ) {
        std::cerr << "Font loading failed!\n";
        exit(0);
    }

    sf::Text textUserName, textPassword;
    textUserName.setFont(font);
    textUserName.setString("Username: ");
    textUserName.setPosition({20.f, 110.f});
    textUserName.setFillColor(sf::Color::Black);

    textPassword.setFont(font);
    textPassword.setString("Password: ");
    textPassword.setPosition({20.f, 260.f});
    textPassword.setFillColor(sf::Color::Black);

    window->draw(textUserName);
    window->draw(textPassword);
}


/*
 * Functions below are for the lobby design
**/

const int lobbyWidth = 600, lobbyHeight = 800;
void lobbyWindowShow() {
    window = new sf::RenderWindow(sf::VideoMode(), "Lobby");
    if ( loadTextures("../src/textures/bg_lobby.jpeg") == false ) { exit(0); }

    while ( window->isOpen() == true ) {
        while ( window->pollEvent(event) ) {
            switch ( event.type ) {
                case sf::Event::Closed:
                    window->close();
                    break;
                default:
                    continue;
            }
        }

        window->clear();
        drawBackground(window);
        window->display();
    }
}

void requestInfo() {

}

/*
 * Functions below are for the playing design
**/

void drawBoard(sf::RenderWindow * &window) {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(margin + i * tileSize, margin + j * tileSize);
            tile.setFillColor(sf::Color(225, 225, 225));
            tile.setOutlineThickness(3);
            tile.setOutlineColor(sf::Color(200, 150, 150));
            window->draw(tile);
        }
    }
}

void drawUI(sf::RenderWindow * &window) {
    sf::Font font;
    if (!font.loadFromFile("Silkscreen-Regular.ttf")) {
        std::cerr << "Font loading failed!\n";
        exit(0);
    }

    // Draw player names
    sf::Text player1Text(player1Name, font, 25);
    player1Text.setPosition(margin, margin - 40);  
    player1Text.setFillColor(sf::Color::Green);  
    window->draw(player1Text);

    sf::Text player2Text(player2Name, font, 25);
    player2Text.setPosition(windowSize + margin - player2Text.getLocalBounds().width, margin - 40);  
    player2Text.setFillColor(sf::Color::Red);  
    window->draw(player2Text);

    // Draw turn count
    sf::Text turnCountText("Turn: " + std::to_string(turnCount), font, 20);
    turnCountText.setPosition(windowSize + margin - turnCountText.getLocalBounds().width, windowSize + margin);
    window->draw(turnCountText);
    
    // Draw chat log frame
    sf::RectangleShape chatLogFrame(sf::Vector2f(chatLogWidth, chatLogHeight));
    chatLogFrame.setPosition(windowSize + 2 * margin, 2 * margin);
    chatLogFrame.setFillColor(sf::Color(225, 225, 225));
    chatLogFrame.setOutlineThickness(2.5);
    chatLogFrame.setOutlineColor(sf::Color(200, 150, 150));
    window->draw(chatLogFrame);
    
    // Draw chat log
    sf::Text chatTitle("Chat Log:", font, 20);
    chatTitle.setPosition(windowSize + margin * 2, margin);  
    window->draw(chatTitle);

    for (size_t i = 0; i < chatLog.size(); ++i) {
        sf::Text messageText(chatLog[i].sender + ": " + chatLog[i].message, font, 16);
        messageText.setPosition(windowSize + margin * 2, margin + 30 + i * 20);  
        window->draw(messageText);
    }
}

void playWindowShow() {
    window = new sf::RenderWindow(sf::VideoMode(playWidth, playHeight), "Gomoku");
    if ( loadTextures("../src/textures/bg_wood.jpg") == false ) { exit(0); }

    while ( window->isOpen() == true ) {
        sf::Event event;
        while ( window->pollEvent(event) == true ) {
            switch ( event.type ) {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if ( event.mouseButton.button == sf::Mouse::Left ) {
                        currentPlayer = (currentPlayer == Player::Player1) ? Player::Player2 : Player::Player1;
                        turnCount++;
                    }
            }
        } 
        
	
        window->clear();

        drawBackground(window);  
        drawBoard(window);
        drawUI(window);

        window->display();
    }
    delete window;
}

#endif
