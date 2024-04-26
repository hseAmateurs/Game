#include <iostream>
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "map/map.h"
#include "map/positions.h"
#include "map/hexagon.h"
#include "Hero.h"
#include "view.h"


int main()
{
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(settings::screen::WIDTH, settings::screen::HEIGHT), "My window");
    Map mt;
    view.reset(sf::FloatRect(0, 0, 1200, 800));

    Hero hero("../../../src/textures/blue_hero.png", 200, 200, 150, 150);

    // access to the time
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time elapsed = clock.restart();

        window.clear(sf::Color(100,100,100));
        // update hero actions and view parameters
        hero.update(time,sf::Mouse::getPosition(window));
        changeView(time, 1200, 800);

        // set camera view
        window.setView(view);

        // clear the window with green color
        window.clear(sf::Color(96, 244, 59));

        // draw a grid
        sf::RectangleShape col(sf::Vector2f(2,10000));
        sf::RectangleShape row(sf::Vector2f(10000,2));
        for (int i = 0; i < 10000; i+=50) {
            col.setPosition(i-5000,-5000);
            window.draw(col);
            row.setPosition(-5000,i-5000);
            window.draw(row);
        }

        mt.draw(window);
        hero.drawHero(window);

        mt.updateDestroying(elapsed);

        window.display();
    }

    return 0;
}