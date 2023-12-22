#include "HomeScreen.hpp"

HomeScreen::HomeScreen() 
    : window(sf::VideoMode(830, 540), "Home Screen"), 
      onlinePlayerCount("Online Players: ", font, 24), // String 
      inGamePlayerCount("In-Game Players: ", font, 24), // String
      okButton(sf::Vector2f(56, 28)),
      readyButton(sf::Vector2f(80, 30)),
      margin(40),
      subMargin(30),
      nameEntered(false), 
      isReady(false),
      onlinePlayerNum(0), // Actually keeps track of number of online players (All connected clients w/ !isReady)
      inGamePlayerNum(0) { // Actually keeps track of number of in-game players (All connected clients w/ isReady, or num of game thread * 2)
    if (!loadTextures()) {
        std::cerr << "Failed to load textures!" << std::endl;
        std::exit(1);
    }    
}

bool HomeScreen::loadTextures() {
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

void HomeScreen::drawBackground() {
    sf::RectangleShape background(sf::Vector2f(830, 540));
    if (woodTexture.getSize().x > 0 && woodTexture.getSize().y > 0) {
        background.setTexture(&woodTexture);
    } else {
        std::cout << "Invalid wooden texture size!" << std::endl;
    }
    window.draw(background);
}

void HomeScreen::drawUI() {
    
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    // Title
    sf::Text titleText("GOMOKU", font, 100);
    titleText.setFillColor(sf::Color(0, 150, 0)); 
    // Author
    sf::Text creatorText("By: S.F. HWANG, J.Y. YEH", font, 36);
    creatorText.setFillColor(sf::Color(200, 50, 0)); 
    // Initialization of variables
    sf::Text enterNameText("Name: ", font, 24); 
    sf::RectangleShape nameInputFrame(sf::Vector2f(200, 28));
    sf::Text okButtonText("OK", font, 20);	
    sf::Text readyButtonText(" Ready", font, 18);
    
    if (!nameEntered) { // The state when client hasn't entered its user name.
    	
    	titleText.setPosition(10 * margin + 0.25 * subMargin - 0.5 * titleText.getLocalBounds().width, 2 * margin);
    	window.draw(titleText);
    	
    	creatorText.setPosition(10 * margin + 0.5 * subMargin - 0.5 * creatorText.getLocalBounds().width, 6 * margin);
    	window.draw(creatorText);
    	
    	enterNameText.setPosition(10 * margin + 0.5 * subMargin 
    					- 0.5 * (enterNameText.getLocalBounds().width + nameInputFrame.getLocalBounds().width + okButton.getLocalBounds().width),
    					 10 * margin);
    	window.draw(enterNameText);
    
    	nameInputFrame.setPosition(10 * margin + 0.5 * subMargin + enterNameText.getLocalBounds().width
    					 - 0.5 * (enterNameText.getLocalBounds().width + nameInputFrame.getLocalBounds().width + okButton.getLocalBounds().width),
    					  10 * margin);
    	nameInputFrame.setOutlineThickness(3);
    	nameInputFrame.setOutlineColor(sf::Color(100, 100, 100));
    	nameInputFrame.setFillColor(sf::Color(225, 225, 225)); 
    	window.draw(nameInputFrame);
    
    	okButton.setPosition(10 * margin + 0.75 * subMargin + enterNameText.getLocalBounds().width + nameInputFrame.getLocalBounds().width
    					- 0.5 * (enterNameText.getLocalBounds().width + nameInputFrame.getLocalBounds().width + okButton.getLocalBounds().width),
    					 10 * margin);
    	okButton.setOutlineThickness(3);
    	okButton.setOutlineColor(sf::Color(100, 100, 100));
    	if (okButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            okButton.setFillColor(sf::Color(100, 100, 255));
        } else {
            okButton.setFillColor(sf::Color(200, 200, 200));
        }
    	window.draw(okButton);
    	
    	playerNameText.setFont(font);
    	playerNameText.setCharacterSize(22);
    	playerNameText.setFillColor(sf::Color(0, 128, 0)); 
    	playerNameText.setPosition(10 * margin + 0.65 * subMargin + enterNameText.getLocalBounds().width
    					 - 0.5 * (enterNameText.getLocalBounds().width + nameInputFrame.getLocalBounds().width + okButton.getLocalBounds().width),
    					  10 * margin);
    	window.draw(playerNameText);
    	
    	okButtonText.setFont(font);
    	okButtonText.setCharacterSize(22);
    	okButtonText.setPosition(10 * margin + 0.75 * subMargin + enterNameText.getLocalBounds().width + nameInputFrame.getLocalBounds().width
    					- 0.5 * (enterNameText.getLocalBounds().width + nameInputFrame.getLocalBounds().width) - 0.75 * okButtonText.getLocalBounds().width,
    					 10 * margin);
    	if (okButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            okButtonText.setFillColor(sf::Color(255, 255, 255));
        } else {
            okButtonText.setFillColor(sf::Color(0, 0, 0));
        }
    	window.draw(okButtonText);
    }
    
    else { // After client pressed ok button. 
    	titleText.setCharacterSize(60);
   	titleText.setPosition(10 * margin + 0.25 * subMargin - 0.5 * titleText.getLocalBounds().width, 1 * margin);
    	window.draw(titleText);
    	
    	creatorText.setCharacterSize(18);
    	creatorText.setPosition(10 * margin + 0.5 * subMargin - 0.5 * creatorText.getLocalBounds().width, 3 * margin);
    	window.draw(creatorText);
    
    	
    	onlinePlayerCount.setPosition(5 * margin + 0.25 * subMargin - 0.5 * onlinePlayerCount.getLocalBounds().width, 8 * margin);
    	window.draw(onlinePlayerCount);
    	
    	
    	/*-----------------------------------------*/
    	//Need to update this number based on what it received from server.
    	onlinePlayerNum = 5;
    	/*-----------------------------------------*/
    	
    	sf::Text oPN(std::to_string(onlinePlayerNum), font, 24);
    	oPN.setPosition(5 * margin + 0.25 * subMargin + 0.5 * onlinePlayerCount.getLocalBounds().width - 0.5 * oPN.getLocalBounds().width, 8 * margin);
    	window.draw(oPN);
    	
    	inGamePlayerCount.setPosition(15 * margin + 0.5 * subMargin - 0.5 * inGamePlayerCount.getLocalBounds().width, 8 * margin);
    	window.draw(inGamePlayerCount);
    	
    	/*-----------------------------------------*/
    	//Need to update this number based on what it received from server.
    	inGamePlayerNum = 4;
    	/*-----------------------------------------*/
    	sf::Text iGPN(std::to_string(inGamePlayerNum), font, 24);
    	iGPN.setPosition(15 * margin + 0.5 * subMargin + 0.5 * inGamePlayerCount.getLocalBounds().width - 0.5 * iGPN.getLocalBounds().width, 8 * margin);
    	window.draw(iGPN);
    	
    	helloPlayerText.setFont(font);
    	helloPlayerText.setCharacterSize(40);
    	helloPlayerText.setPosition(10 * margin + 0.25 * subMargin - 0.5 * helloPlayerText.getLocalBounds().width, 5 * margin);
    	helloPlayerText.setFillColor(sf::Color(0, 128, 128)); 
    	window.draw(helloPlayerText);
    	
    	readyButton.setPosition(10 * margin + 0.65 * subMargin - 0.5 * readyButton.getLocalBounds().width, 10 * margin);
    	readyButton.setOutlineThickness(3);
    	readyButton.setOutlineColor(sf::Color(100, 100, 100));
    	if (readyButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            readyButton.setFillColor(sf::Color(100, 100, 255));
        } else {
            readyButton.setFillColor(sf::Color(200, 200, 200));
        }
    	window.draw(readyButton);
    	
    	
    	readyButtonText.setPosition(10 * margin + 0.35 * subMargin - 0.5 * readyButtonText.getLocalBounds().width, 10 * margin);
    	if (okButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            okButtonText.setFillColor(sf::Color(255, 255, 255));
        } else {
            okButtonText.setFillColor(sf::Color(0, 0, 0));
        }
    	window.draw(readyButtonText);

    }
}

void HomeScreen::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } 
        else if (event.type == sf::Event::TextEntered) {
            if (!nameEntered) {
                // Handle text input for player name entry, would only be used when player is typing its name.
                if (event.text.unicode < 128) {
                    char typedChar = static_cast<char>(event.text.unicode);
                    if (typedChar == '\b' && !playerNameText.getString().isEmpty()) {
                        // Handle backspace
                        playerNameText.setString(playerNameText.getString().substring(0, playerNameText.getString().getSize() - 1));
                    } else if (typedChar != '\b' && playerNameText.getString().getSize() < 10) {
                        // Append the typed character
                        playerNameText.setString(playerNameText.getString() + typedChar);
                    }
                }
            }
        } else if (event.type == sf::Event::MouseButtonPressed) {
            // Handle mouse button press
            if (okButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                // Handle OK button press
                if (!playerNameText.getString().isEmpty()) {
                    helloPlayerText.setString("Hello, " + playerNameText.getString() + "!");
                    nameEntered = true;
                    /*-----------------------------------------*/
                    // Client should connect to server now, including its name. As server will need to use it when game starts. 
                    // ** Connection variables should NOT be saved in here but should be in the client file instead, as this window will close after the game starts.
                    /*-----------------------------------------*/
                }
            } else if (readyButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                // Handle Ready button press
                isReady = true;
                /*-----------------------------------------*/
                // Client should let server know client is ready to play a game.
                /*-----------------------------------------*/
            }
        }
    }
}


void HomeScreen::run() {
    int gameStart = 0; // In the actual client file, it should keep track of whether game is started, and needs to be able to close this window if it does start. 
    		       // Should change this variable later on.
    while (window.isOpen() && !gameStart) {
    	window.clear();	
    
    	drawBackground();
        handleInput();
        drawUI();
        
        window.display();
	
    }
}

