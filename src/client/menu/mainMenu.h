#ifndef MAINMENU_H
#define MAINMENU_H

#include "menu.h"
#include "menuManager.h"
#include "menuButton.h"

class MainMenu : public Menu {
public:
    MainMenu(const sf::Font& font, MenuManager* menuManager);

    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) override;

    void update(const sf::Time& deltaTime);
    MenuManager* getMenuManager();

private:
    MenuButton quickPlayButton;
    MenuButton joinLobbyButton;
    MenuButton statisticsButton;
    MenuButton friendsButton;
    MenuManager* menuManager;
};

#endif