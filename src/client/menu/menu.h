#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include "menuButton.h"
#include <vector>

class Menu {
public:
    Menu(const std::string& title);

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleInput(const sf::Event& event, sf::RenderWindow& window) = 0;
    virtual ~Menu() {} // Virtual destructor

    std::string getTitle() const { return title; }

protected:
    std::string title;
    std::vector<MenuButton> buttons; 
};

#endif 