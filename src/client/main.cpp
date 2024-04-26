#include <iostream>
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "map/map.h"
#include "map/positions.h"
#include "map/hexagon.h"
#include "heroes/Hero.h"
#include "view.h"


int main()
{
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(settings::screen::WIDTH, settings::screen::HEIGHT), "My window");
    Map mt;
    view.reset(sf::FloatRect(0, 0, settings::screen::WIDTH, settings::screen::HEIGHT));

    Hero hero("../../../src/textures/blue_hero.png", settings::screen::WIDTH/2, settings::screen::HEIGHT/2, 150, 150);

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

        hero.update(elapsed, sf::Mouse::getPosition(window));
        mt.updateDestroying(elapsed);

        changeView(elapsed, settings::screen::WIDTH, settings::screen::HEIGHT);

        // set camera view
        window.setView(view);


        #ifdef GRID
        sf::RectangleShape col(sf::Vector2f(2,10000));
        sf::RectangleShape row(sf::Vector2f(10000,2));
        for (int i = 0; i < 10000; i+=50) {
            col.setPosition(i-5000,-5000);
            window.draw(col);
            row.setPosition(-5000,i-5000);
            window.draw(row);
        }
        #endif


        mt.draw(window);
        hero.draw(window);

        window.display();
    }

    return 0;
}