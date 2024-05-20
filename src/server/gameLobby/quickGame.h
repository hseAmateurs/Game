#ifndef GAME_QUICKGAME_H
#define GAME_QUICKGAME_H

#include <vector>
#include <string>
#include "gameLobby.h"




class QuickGame {
public:
    QuickGame(std::vector<GameLobby*> &activelobbies): activelobbies(activelobbies) {};
    std::string addToQueue(const std::string& username, int clientSocket);
    void loadGameLobby();
    bool isntInQueue(const std::string& username);
    std::string removeFromQueue(const std::string& username);
    bool isPlayerInAnyLobby(const std::string& username);
    bool lobbyCreatedFlag = false;
    GameLobby* pendingLobby = nullptr;
    struct PlayerInfo {
        std::string username;
        int clientSocket;
    };

    //bool isPlayerInAnyLobby(const std::string& username)

    std::string matchmake(const std::string login);

private:
    std::vector<GameLobby*> &activelobbies;


    std::vector<PlayerInfo> playerQueue;




};

#endif //GAME_QUICKGAME_H
