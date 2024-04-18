#include <iostream>
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "view.h"


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "My window");
    view.reset(sf::FloatRect(0, 0, 1200, 800));

    Hero hero("../../../src/textures/blue_hero.png", 200, 200, 150, 150);

    // access to the time
    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // этот блок я с прошлого проекта спиздил тут какая то магия с временем которое для плавного апдейта нужно
        // мб у вас как то по другому было
        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart(); //перезагружает время
        time = time/800; //скорость тиков (чем меньше делитель тем больше скорость)

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // update hero actions and view parameters
        hero.update(time,sf::Mouse::getPosition(window));
        changeView(time, 1200, 800);

        // set camera view
        window.setView(view);

        // clear the window with black color
        window.clear(sf::Color(96, 244, 59));

        // draw everything here...
        hero.drawHero(window);

        // end the current frame
        window.display();
    }

    return 0;
}