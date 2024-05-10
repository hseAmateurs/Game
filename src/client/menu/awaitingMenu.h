#ifndef AWAITINGMENU_H
#define AWAITINGMENU_H

#include "menu.h"
#include "menuButton.h"
#include "menuManager.h"

class AwaitingMenu : public Menu {
public:
    AwaitingMenu(const sf::Font& font, MenuManager* menuManager,Client& client);

    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) override;
    void update(const sf::Time& deltaTime,Client& client);
    MenuManager* getMenuManager();


private:
    sf::Text searchingText;
    sf::Clock animationClock; 
    int currentDotCount = 3; 
    MenuManager* menuManager;
};

#endif