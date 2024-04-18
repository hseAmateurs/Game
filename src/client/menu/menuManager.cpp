#include "MenuManager.h"

void MenuManager::pushMenu(Menu* menu) {
    menus.push(menu);
}

void MenuManager::popMenu() {
    if (!menus.empty()) {
        delete menus.top(); 
        menus.pop();
    }
}

void MenuManager::clearMenus() {
    while (!menus.empty()) {
        popMenu();
    }
}

void MenuManager::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    if (!menus.empty()) {
        menus.top()->handleInput(event, window);
    }
}

void MenuManager::update(const sf::Time& deltaTime) {
    if (!menus.empty()) {
        menus.top()->update(deltaTime); 
    }
}

void MenuManager::draw(sf::RenderWindow& window) const {
    if (!menus.empty()) {
        menus.top()->draw(window);
    }
}