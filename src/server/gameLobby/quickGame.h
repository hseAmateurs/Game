#ifndef GAME_QUICKGAME_H
#define GAME_QUICKGAME_H

#include <vector>
#include <string>
#include "gameLobby.h"




class QuickGame {
public:
//    QuickGame();
    std::string addToQueue(const std::string& username, int clientSocket);
    void loadGameLobby();
    bool isntInQueue(const std::string& username);
    std::string removeFromQueue(const std::string& username);
    bool isPlayerInAnyLobby(const std::string& username);


    //bool isPlayerInAnyLobby(const std::string& username)

    std::string matchmake(const std::string login);

private:
    struct PlayerInfo {
        std::string username;
        int clientSocket;
    };

    std::vector<PlayerInfo> playerQueue;
    std::vector<GameLobby*> activeLobbies;

};

#endif //GAME_QUICKGAME_H
