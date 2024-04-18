#include "AuthorizationMenu.h"

AuthorizationMenu::AuthorizationMenu(const sf::Font& font) :
    Menu("Authorization"),
    usernameField(sf::Vector2f(100, 100), "", font,20),  // Adjust positions as needed
    passwordField(sf::Vector2f(100, 150), "", font,20),
    enterButton(sf::Vector2f(100, 200), "Enter", font, 15),
    backButton(sf::Vector2f(650, 50), "Back", font,15) // Example position for top-right
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
}

void AuthorizationMenu::draw(sf::RenderWindow& window){
    usernameField.draw(window);
    passwordField.draw(window);
    enterButton.draw(window);
    backButton.draw(window);
}

void AuthorizationMenu::update(const sf::Time& deltaTime){
    usernameField.update(deltaTime);
    passwordField.update(deltaTime);
}

void AuthorizationMenu::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    usernameField.handleInput(event,window);
    passwordField.handleInput(event,window);

    if (enterButton.isPressed(window)) {
        //authMenu.~AuthorizationMenu();
    }

    if (backButton.isPressed(window)) {
        // Handle "Back" button press (e.g., go back to the previous menu)
    }
}