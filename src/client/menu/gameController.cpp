#include "gameController.h"

/*
Тут происходит вся игра.
*/

GameController::GameController(const sf::Font& font, MenuManager* menuManager,Client& client) :
    menuManager(menuManager)
{
}


void GameController::run(sf::RenderWindow& window){
    srand(time(nullptr));
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
            if(event.type == sf::Event::KeyPressed)
                field.handleButton(event.key.code);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                field.handleRightClick(sf::Mouse::getPosition(window));
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                field.handleLeftClick(sf::Mouse::getPosition(window));
        }
        sf::Time elapsed = clock.restart();

        field.update(elapsed, sf::Mouse::getPosition(window));

        window.clear(sf::Color(100,100,100));
        changeView(elapsed, event.mouseWheelScroll.delta, sf::Mouse::getPosition(window));
        window.setView(view);
        field.draw(window);
        window.display();
    }
    // этот код тоже требует некоторого рефакторинга для выхода из игры, но это проблема на потом
}