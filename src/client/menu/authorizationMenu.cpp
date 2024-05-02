#include "AuthorizationMenu.h"
#include "menuManager.h"
#include "mainMenu.h"
#include <iostream>

AuthorizationMenu::AuthorizationMenu(const sf::Font& font, MenuManager* menuManager) :
    Menu("Authorization"),
    usernameField(sf::Vector2f(400, 100), "", font,20),  // Adjust positions as needed
    passwordField(sf::Vector2f(400, 150), "", font,20),
    enterButton(sf::Vector2f(400, 200), "Enter", font, 15),
    backButton(sf::Vector2f(850, 50), "Back", font,15), // Example position for top-right
    menuManager(menuManager)
{
    // Customize Text Fields
    usernameField.setBackgroundColor(sf::Color::Black); // Light gray background
    usernameField.setSize(200.f, 30.f); 

    passwordField.setBackgroundColor(sf::Color::Black);
    passwordField.setSize(200.f, 30.f);

    enterButton.setSize(100.f, 40.f);
    enterButton.setButtonColor(sf::Color(0, 150, 0)); // Green
    enterButton.setHoverColor(sf::Color(0, 200, 0)); // Brighter green

    backButton.setSize(80.f, 30.f);
    backButton.setButtonColor(sf::Color(150, 0, 0)); // Red
    backButton.setHoverColor(sf::Color(200, 0, 0)); // Brighter red
    
    loginLabel.setFont(font);
    loginLabel.setString("Login:");
    loginLabel.setCharacterSize(20); // Adjust size as needed
    loginLabel.setFillColor(sf::Color::White);
    loginLabel.setPosition(50.f, 105.f); // Example position 

    passwordLabel.setFont(font);
    passwordLabel.setString("Password:");
    passwordLabel.setCharacterSize(20); 
    passwordLabel.setFillColor(sf::Color::White);
    passwordLabel.setPosition(50.f, 155.f); // Example position

    errorMessage.setFont(font);
    errorMessage.setString(""); // Start with an empty string
    errorMessage.setCharacterSize(13); // Adjust size as needed 
    errorMessage.setFillColor(sf::Color::Red);
    errorMessage.setPosition(50.f, 250.f); // Example position (below the buttons)
}


void AuthorizationMenu::draw(sf::RenderWindow& window){
    usernameField.draw(window);
    passwordField.draw(window);
    enterButton.draw(window);
    backButton.draw(window);
    window.draw(loginLabel);
    window.draw(passwordLabel);
    window.draw(errorMessage);
}

MenuManager* AuthorizationMenu::getMenuManager() {
    return menuManager; 
}

void AuthorizationMenu::update(const sf::Time& deltaTime){
    usernameField.update(deltaTime);
    passwordField.update(deltaTime);
}

void AuthorizationMenu::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) {
    usernameField.handleInput(event,window);
    passwordField.handleInput(event,window);

    if (enterButton.isPressed(window)) {
        std::string username=usernameField.getText();
        std::string password=passwordField.getText();
        MenuManager* menuManager=getMenuManager();
        if(menuManager){
            std::string message;
            message="100 "+username+" "+password;
            const char* msg=message.c_str();
            client.sendMessage(msg);
            message=client.getMessage();
            if(message=="0"){
                client.setLogin(username);
                menuManager->pushMenu(new MainMenu(menuManager->getFont(),menuManager,client));
            }
            else if(message=="1"){
                errorMessage.setString("Wrong password.");
            }
            else if(message=="2"){
                errorMessage.setString("No such login exists.");
            }
        }
    }

    if (backButton.isPressed(window)) {
        MenuManager* menuManager = getMenuManager();
        if(menuManager){
            menuManager->popMenu();
        } 
    }
}