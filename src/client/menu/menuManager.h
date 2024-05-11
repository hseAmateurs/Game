#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <SFML/Graphics.hpp>
#include <stack>
#include "menu.h" 

class MenuManager {
public:
    void setFont(const sf::Font& font) { this->font = font; } // Set the font for menus

    void pushMenu(Menu* menu);  // Add a menu to the top
    void popMenu();           // Remove the top menu 
    void clearMenus();         // Remove all menus 

    Menu* getCurrentMenu() {return menus.top(); }

    void handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client);
    void update(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window) const;

    const sf::Font& getFont() const { return font; }

private:
    std::stack<Menu*> menus;
    sf::Font font; 
};

#endif