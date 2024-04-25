#include "MenuManager.h"
#include <iostream>

void MenuManager::pushMenu(Menu* menu) {
    menus.push(menu);
}

void MenuManager::popMenu() {
    if (!menus.empty()) {
        delete menus.top();
        menus.pop();
    }
    else
        std::cerr << "Error: Cannot pop menu from an empty stack!" << std::endl;
}

void MenuManager::clearMenus() {
    while (!menus.empty()) {
        popMenu();
    }
}

void MenuManager::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) {
    if (!menus.empty()) {
        menus.top()->handleInput(event, window,client);
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