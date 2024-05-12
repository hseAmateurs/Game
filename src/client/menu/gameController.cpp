#include "gameController.h"

/*
Тут происходит вся игра.
*/

GameController::GameController(const sf::Font& font, MenuManager* menuManager,Client& client) :
    menuManager(menuManager)
{
}


void GameController::run(sf::RenderWindow& window,Client& client){
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
            sf::Vector2i mousePos=sf::Mouse::getPosition(window);
            std::string mouseposx;
            std::string mouseposy;
            bool flag=false;
            int cn=0;
            if(mousePos.x>0)
                mouseposx="+"+std::to_string(mousePos.x);
            else
                mouseposx=std::to_string(mousePos.x);
            if(mousePos.y>0)
                mouseposy="+"+std::to_string(mousePos.y);
            else
                mouseposy=std::to_string(mousePos.y);
            if (event.type == sf::Event::Closed)
                window.close();
            std::string message="701 "+client.getLogin();
            if(event.type==sf::Event::TextEntered)
                message=message+" 1 "+static_cast<char>(event.text.unicode);
            else{
                message+=" 0 0";
                cn++;
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)||sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    message+=" 1 2 "+mouseposx+mouseposy;
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    message+=" 1 1 "+mouseposx+mouseposy;
            }
            else{
                message+=" 0 0 "+mouseposx+mouseposy;
                cn++;
            }
            if(cn!=2)
                client.sendMessage(message.c_str());
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