#ifndef GAME_GAMELOBBY_H
#define GAME_GAMELOBBY_H

#include <vector>
#include <string>
#include "../game/core/field.h"
#include "../game/core/assets.h"



class GameLobby {
public:
    int test = 10;

    void addPlayer(const std::string& username, int clientSocket);
    void notifyPlayers(const std::string& message);
    bool hasPlayer(const std::string& username);
    void gameLoop();//обрабатывает карту и возвращает информацию игрокам
    void setNames();
    std::vector<int> playerSockets;
    std::vector<std::string> playerLogins;
private:
    Assets assets;
    Field field;
};



#endif //GAME_GAMELOBBY_H
