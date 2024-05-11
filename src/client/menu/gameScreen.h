#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "menu.h"
#include "menuButton.h"
#include "textField.h"
#include "menuManager.h"
#include "friendEntry.h"

class GameScreen : public Menu {
public:
    GameScreen(const sf::Font& font, MenuManager* menuManager,Client& client);

    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) override;
    void update(const sf::Time& deltaTime,Client& client);
    MenuManager* getMenuManager();

private:
    MenuManager* menuManager;
};

#endif