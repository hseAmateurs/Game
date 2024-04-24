#include <iostream>
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "map/map.h"
#include "map/positions.h"
#include "map/hexagon.h"


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(settings::screen::WIDTH, settings::screen::HEIGHT), "My window");
    Map mt;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color(100,100,100));

        // draw everything here...
        // window.draw(...);
        mt.draw(window);


        // end the current frame
        window.display();
    }

    return 0;
}