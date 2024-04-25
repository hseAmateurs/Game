#ifndef STARTMENU_H
#define STARTMENU_H

#include <SFML/Graphics.hpp>
#include "menu.h"
#include "menuButton.h"
#include "menuManager.h"

class StartMenu : public Menu {
public:
    StartMenu(const sf::Font& font, MenuManager* menuManager);

    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) override;
    MenuManager* getMenuManager();

private:
    MenuButton loginButton;
    MenuButton registerButton;
    MenuManager* menuManager;
};

#endif