#ifndef CREATEJOINMENU_H
#define CREATEJOINMENU_H

#include "menu.h"
#include "menuButton.h"
#include "menuManager.h"

class CreateJoinMenu : public Menu {
public:
    CreateJoinMenu(const sf::Font& font, MenuManager* menuManager,Client& client);

    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) override;
    MenuManager* getMenuManager();

private:
    MenuButton createButton;
    MenuButton joinButton;
    MenuButton backButton;
    MenuManager* menuManager;
};

#endif