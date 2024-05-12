#include "Controller.h"
#include "gameController.h"

Controller::Controller() : 
    window(sf::VideoMode(1920, 1080), "Game")
{}

void Controller::run() {
    window.setFramerateLimit(60);
    font.loadFromFile("PressStart2P-Regular.ttf");
    MenuManager menuManager;
    menuManager.setFont(font);
    StartMenu startMenu(font, &menuManager);
    menuManager.pushMenu(&startMenu);
    Client client("127.0.0.1", 8080); // Создаем клиента, подключающегося к localhost:8080
    //Client client("192.168.201.60", 8080); // для подключения к другому устройству через локальную сеть нужно ввести ipv4 адапрера беспроводной сети(cmd: ipconfig)
    client.start(); // Запускаем клиент
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            menuManager.handleInput(event, window,client);
        }

        sf::Time deltaTime = clock.restart();
        menuManager.update(deltaTime,client);

        window.clear(sf::Color(50,50,50));
        menuManager.draw(window);
        window.display();
        if(menuManager.getCurrentMenu()->getTitle()=="GameScreen"){ // Если запущена игра, то палку перехватывает gameController.
            GameController gameController(menuManager.getFont(),&menuManager,client);
            gameController.run(window,client);
        }
    }
}