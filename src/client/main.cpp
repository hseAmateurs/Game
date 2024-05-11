#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils/settings.h"
#include "map/map.h"
#include "heroes/Hero.h"
#include "core/view.h"
#include "core/assets.h"
#include "core/field.h"
#include "map/tree.h"


int main()
{
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(settings::screen::WIDTH, settings::screen::HEIGHT), "My window");
    Assets assets;
    Field field;

    view.reset(sf::FloatRect(0, 0, settings::screen::WIDTH, settings::screen::HEIGHT));

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                field.handleRightClick(sf::Mouse::getPosition(window));
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                field.handleLeftClick(sf::Mouse::getPosition(window));
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                field.handleButtonQ();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                field.handleButtonW();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                field.handleButtonE();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                field.handleButtonR();
        }
        sf::Time elapsed = clock.restart();

        field.update(elapsed, sf::Mouse::getPosition(window));

        window.clear(sf::Color(100,100,100));
        changeView(elapsed, event.mouseWheelScroll.delta, sf::Mouse::getPosition(window));
        window.setView(view);
        field.draw(window);
        window.display();
    }

    return 0;
}