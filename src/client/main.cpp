#include <iostream>
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "map/map.h"
#include "map/positions.h"
#include "map/hexagon.h"


int main()
{
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(settings::screen::WIDTH, settings::screen::HEIGHT), "My window");
    Map mt;

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

        mt.draw(window);

        mt.updateDestroying(elapsed);

        window.display();
    }

    return 0;
}