#ifndef GAME_QUICKGAME_H
#define GAME_QUICKGAME_H
#include <iostream>
#include <vector>


class QuickGame {
public:
    std::string addToQueue(std::string login); // add user in quick play lobby
    void loadGameLobby(); // replace user for QP lobby to game lobby
    bool isntInQueue(std::string login);




private:
    std::vector<std::string> lobbyQueue;


};


#endif //GAME_QUICKGAME_H
