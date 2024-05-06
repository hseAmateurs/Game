#include "startMenu.h"
#include "authorizationMenu.h"
#include "registrationMenu.h"
#include "menuManager.h" // For accessing the MenuManager

StartMenu::StartMenu(const sf::Font& font, MenuManager* menuManager) :
    Menu("Start Menu"),
    loginButton(sf::Vector2f(710, 400), "Login", font),
    registerButton(sf::Vector2f(710, 600), "Register", font),
    menuManager(menuManager)
{
    loginButton.setSize(500.f, 100.f);
    registerButton.setSize(500.f, 100.f);

}

void StartMenu::draw(sf::RenderWindow& window) {
    loginButton.draw(window);
    registerButton.draw(window);
}

MenuManager* StartMenu::getMenuManager() {
    return menuManager; 
}

void StartMenu::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) {
    if (loginButton.isPressed(window)) {
        MenuManager* menuManager = getMenuManager();
        if (menuManager) {
            menuManager->pushMenu(new AuthorizationMenu(menuManager->getFont(),menuManager));
        }
    } 

    if (registerButton.isPressed(window)) {
        MenuManager* menuManager = getMenuManager();
        if (menuManager) {
            menuManager->pushMenu(new RegistrationMenu(menuManager->getFont(),menuManager));
        }
    }
}

