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
            if(event.type==sf::Event::TextEntered){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                    std::string message;
                    message="701 "+client.getLogin()+" "+static_cast<char>(event.text.unicode)+" 2 "+mouseposx+mouseposy;
                    client.sendMessage(message.c_str());
                    flag=true;
                }
                else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    std::string message;
                    message="701 "+client.getLogin()+" "+static_cast<char>(event.text.unicode)+" 1 "+mouseposx+mouseposy;
                    client.sendMessage(message.c_str());
                    flag=true;
                }
                else if(flag==false){
                    std::string message;
                    message="702 "+client.getLogin()+" "+static_cast<char>(event.text.unicode)+" "+mouseposx+mouseposy;
                    client.sendMessage(message.c_str());
                    // only key pressed
                }
            }
            else if(flag==false){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                    std::string message;
                    message="703 "+client.getLogin()+" 2 "+mouseposx+mouseposy;
                    client.sendMessage(message.c_str());
                }
                else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    std::string message;                           
                    message="703 "+client.getLogin()+" 1 "+mouseposx+mouseposy;
                    client.sendMessage(message.c_str());
                }
            }
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