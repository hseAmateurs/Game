#include "startMenu.h"
#include "authorizationMenu.h"
#include "menuManager.h" // For accessing the MenuManager

StartMenu::StartMenu(const sf::Font& font, MenuManager* menuManager) :
    Menu("Start Menu"),
    loginButton(sf::Vector2f(100, 100), "Login", font),
    registerButton(sf::Vector2f(100, 150), "Register", font),
    menuManager(menuManager)
{
    // Customize button appearance (sizes, colors) if needed
}

void StartMenu::draw(sf::RenderWindow& window) {
    loginButton.draw(window);
    registerButton.draw(window);
}

MenuManager* StartMenu::getMenuManager() {
    return menuManager; 
}

void StartMenu::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    if (loginButton.isPressed(window)) {
        // Switch to AuthorizationMenu
        MenuManager* menuManager = getMenuManager();
        if (menuManager) {
            menuManager->pushMenu(new AuthorizationMenu(menuManager->getFont(),menuManager));
        }
    } 

    if (registerButton.isPressed(window)) {
        // Handle "Register" button press (add your logic later)
    }
}

