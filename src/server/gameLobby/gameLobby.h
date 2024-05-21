#ifndef GAME_GAMELOBBY_H
#define GAME_GAMELOBBY_H

#include <vector>
#include <string>
#include "../game/core/field.h"
#include "../game/core/assets.h"
#include <time.h>



class GameLobby {
public:

    GameLobby (): field(), assets() { std::cout << "LOBBY CREATED\n" ;}
    int test = 10;

    void addPlayer(const std::string& username, int clientSocket);
    bool hasPlayer(const std::string& username);
    void gameLoop();//обрабатывает карту и возвращает информацию игрокам
    void setNames();
    std::vector<int> playerSockets;
    std::vector<std::string> playerLogins;
private:
    Assets assets;
    Field field;
    sf::Clock lobbyClock;
};



#endif //GAME_GAMELOBBY_H
