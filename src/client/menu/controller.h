#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H


#include <SFML/Graphics.hpp>
#include "textField.h"
#include "menuButton.h"
#include "startMenu.h"
#include "registrationMenu.h"
#include "menuManager.h"
#include "authorizationMenu.h"
#include <iostream>

class Controller {
public:
    Controller();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
};


#endif