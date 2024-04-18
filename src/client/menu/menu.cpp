#include "Menu.h"

Menu::Menu(const std::string& title) : title(title) {
    // You can add any common initialization for all menus here, 
    // such as setting up the background or default button styles.
}


void Menu::draw(sf::RenderWindow& window) {}

void Menu::handleInput(const sf::Event& event, sf::RenderWindow& window) {}

void Menu::update(const sf::Time& deltaTime) {}