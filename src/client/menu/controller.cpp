#include "Controller.h"

Controller::Controller() : 
    window(sf::VideoMode(1920, 1080), "Game")
{
    
}

void Controller::run() {
    window.setFramerateLimit(60);
    font.loadFromFile("PressStart2P-Regular.ttf");
    MenuManager menuManager;
    menuManager.setFont(font);
    StartMenu startMenu(font, &menuManager);
    menuManager.pushMenu(&startMenu);
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            menuManager.handleInput(event, window);
        }

        sf::Time deltaTime = clock.restart();
        menuManager.update(deltaTime);

        window.clear(sf::Color(50,50,50));
        menuManager.draw(window);
        window.display();
    }
}