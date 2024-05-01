#include "quickGame.h"

std::string QuickGame::addToQueue(std::string login) {
    lobbyQueue.push_back(login);
    return "0";
}

void  QuickGame::loadGameLobby() {
    std::vector<std::string> toGame;

    if (lobbyQueue.size() >= 3) {
        toGame.push_back(lobbyQueue.back());
        lobbyQueue.pop_back();
        toGame.push_back(lobbyQueue.back());
        lobbyQueue.pop_back();
        toGame.push_back(lobbyQueue.back());
        lobbyQueue.pop_back();

        std::cout << toGame[0] << " " << toGame[1] << " " << toGame[2];
    }
    //smth happens and game starts
}

bool QuickGame::isntInQueue(std::string login) {
    for (auto p : lobbyQueue){
        if (login == p){
            return false;
        }
    }
    return true;

}

