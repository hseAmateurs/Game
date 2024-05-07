#ifndef GAME_GAMELOBBY_H
#define GAME_GAMELOBBY_H

#include <vector>
#include <string>



class GameLobby {
public:
    int test = 10;

    void addPlayer(const std::string& username, int clientSocket);
    void notifyPlayers(const std::string& message);
    bool hasPlayer(const std::string& username);
    void gameLoop();//обрабатывает карту и возвращает информацию игрокам
    std::vector<int> playerSockets;
    std::vector<std::string> playerLogins;
private:
    //Map map;
    //Hero hero1, hero2, hero3;
    //any game info;

};



#endif //GAME_GAMELOBBY_H
