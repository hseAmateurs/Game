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

void GameLobby::notifyPlayers(const std::string& message) {
    for (int clientSocket : playerSockets) {
        //server.sendMessage(clientSocket, message.c_str());
    }
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
    test+=1;
}





