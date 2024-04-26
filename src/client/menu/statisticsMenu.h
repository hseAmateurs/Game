#ifndef STATISTICSMENU_H
#define STATISTICSMENU_H

#include "menu.h"
#include "menuButton.h"
#include "menuManager.h"

class StatisticsMenu : public Menu {
public:
    StatisticsMenu(const sf::Font& font, MenuManager* menuManager,Client& client);

    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) override;
    MenuManager* getMenuManager();

private:
    MenuManager* menuManager;
    sf::Text statistics;
    MenuButton backButton;
};

#endif