#include "registrationMenu.h"
#include "menuManager.h"
#include <iostream>

RegistrationMenu::RegistrationMenu(const sf::Font& font, MenuManager* menuManager) :
    Menu("Registration"),
    usernameField(sf::Vector2f(400, 100), "", font,20),  // Adjust positions as needed
    passwordField(sf::Vector2f(400, 150), "", font,20),
    enterButton(sf::Vector2f(400, 200), "Enter", font, 15),
    backButton(sf::Vector2f(850, 50), "Back", font,15),  // Example position for top-right
    menuManager(menuManager)
{
    // Customize Text Fields
    usernameField.setBackgroundColor(sf::Color::Black); // Light gray background
    usernameField.setSize(200.f, 30.f); 

    passwordField.setBackgroundColor(sf::Color::Black);
    passwordField.setSize(200.f, 30.f);

    // Customize Buttons (example colors and sizes)
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

bool RegistrationMenu::isValidLogin(const std::string& username, const std::string& password) {
    // Check username length
    if (username.length() < 3) {
        return false;
    }

    // Check password length and characters
    if (password.length() < 6) {
        return false;
    }
    for (char c : password) {
        if (!isalnum(c) && !ispunct(c)) {
            return false; // Invalid character found
        }
    }
    return true; // Credentials are valid
}


void RegistrationMenu::draw(sf::RenderWindow& window){
    usernameField.draw(window);
    passwordField.draw(window);
    enterButton.draw(window);
    backButton.draw(window);
    window.draw(loginLabel);
    window.draw(passwordLabel);
    window.draw(errorMessage);
}

MenuManager* RegistrationMenu::getMenuManager(){
    return menuManager; 
}

void RegistrationMenu::update(const sf::Time& deltaTime){
    usernameField.update(deltaTime);
    passwordField.update(deltaTime);
}

void RegistrationMenu::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    usernameField.handleInput(event,window);
    passwordField.handleInput(event,window);
    if (enterButton.isPressed(window)) {
        std::string username=usernameField.getText();
        std::string password=passwordField.getText();
        if(isValidLogin(username,password)){
            MenuManager* menuManager=getMenuManager();
            if(menuManager){
                // Где-то здесь должна происходить отправка данных на сервер.
                std::cout << "here";
            }
        }
        else{
            errorMessage.setString("Oops, looks like something's wrong.\n\nYour password has to be more than 6 characters long and your username has to be more than 3 characters long.\n\nPlease verify that that is the case.");
        }
    }

    if (backButton.isPressed(window)) {
        MenuManager* menuManager = getMenuManager();
        if(menuManager){
            menuManager->popMenu();
        } 
    }
}