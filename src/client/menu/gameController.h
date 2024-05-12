#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../utils/settings.h"
#include "../map/map.h"
#include "../heroes/Hero.h"
#include "../core/view.h"
#include "../core/assets.h"
#include "../core/field.h"
#include "../map/tree.h"
#include "menu.h"
#include "menuManager.h"
#include "../client.h"

class GameController {
public:
    GameController(const sf::Font& font, MenuManager* menuManager,Client& client);
    void run(sf::RenderWindow& window,Client& client);

private:
    sf::RenderWindow window;
    sf::Font font;
    MenuManager* menuManager;

};

#endif