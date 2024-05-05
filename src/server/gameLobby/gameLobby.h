#ifndef GAME_GAMELOBBY_H
#define GAME_GAMELOBBY_H

#include <vector>
#include <string>



class GameLobby {
public:
//    GameLobby();
//    ~GameLobby();

    void addPlayer(const std::string& username, int clientSocket);
    void notifyPlayers(const std::string& message);
    bool hasPlayer(const std::string& username);

private:
    std::vector<int> playerSockets;
    std::vector<std::string> playerLogins;
};

#endif //GAME_GAMELOBBY_H
