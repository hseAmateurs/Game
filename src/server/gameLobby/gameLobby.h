#ifndef GAME_GAMELOBBY_H
#define GAME_GAMELOBBY_H

#include <vector>
#include <string>
#include "../game/core/field.h"
#include "../game/core/assets.h"
#include "../game/utils/settings.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../game/map/map.h"
#include "../game/heroes/Hero.h"
#include "../game/core/view.h"
#include "../game/core/assets.h"
#include "../game/core/field.h"



class GameLobby {
public:
    GameLobby(): window(sf::VideoMode(settings::screen::WIDTH, settings::screen::HEIGHT), "My window")
    {
        std::cout << "Window created" << std::endl;
    }
    int test = 10;

    void addPlayer(const std::string& username, int clientSocket);
    void notifyPlayers(const std::string& message);
    bool hasPlayer(const std::string& username);
    void gameLoop();//обрабатывает карту и возвращает информацию игрокам
    void setNames();
    std::vector<int> playerSockets;
    std::vector<std::string> playerLogins;
private:
    sf::RenderWindow window;
    Assets assets;
    Field field;
    sf::Clock clock;
};



#endif //GAME_GAMELOBBY_H
