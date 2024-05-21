#include "gameLobby.h"
#include <algorithm>
#include "../../common.h"
#include <algorithm>
#include <memory>


void GameLobby::addPlayer(const std::string& username, int clientSocket) {
    playerLogins.push_back(username);
    playerSockets.push_back(clientSocket);
    // ... (Potentially store username and other player data) ...
}

bool GameLobby::hasPlayer(const std::string& username) {
    for (const auto& player : playerLogins) {
        if (player == username) {
            return true; // Player found in this lobby
        }
    }
    return false; // Player not found in this lobby
}

void GameLobby::gameLoop() {
    sf::Time elapsed = lobbyClock.restart();
    field.update(elapsed);
    //std::cout<<field.countHex()<<"\n";
}

void GameLobby::setNames() {
    field.setNames(playerLogins);
}




