#include "quickGame.h"
#include "gameLobby.h"


std::string QuickGame::addToQueue(const std::string& username, int clientSocket) {
    PlayerInfo player;
    player.username = username;
    player.clientSocket = clientSocket;
    playerQueue.push_back(player);
    return "0";//success
}


std::string QuickGame::matchmake(const std::string login) {

    if (playerQueue.size() >= 3 && !isPlayerInAnyLobby(login) && !isntInQueue(login) && !lobbyCreatedFlag) { // Check if we have enough players for a lobby
        // Create a new GameLobby instance
        lobbyCreatedFlag = true;
        GameLobby* newLobby = new GameLobby();

        // Add the first 3 players to the lobby
        for (int i = 1; i <= 3; ++i) {
            newLobby->addPlayer(playerQueue[playerQueue.size() - i].username, playerQueue[playerQueue.size() - i].clientSocket);
        }
        newLobby->setNames();

        // Remove those players from the queue
        playerQueue.pop_back();
        playerQueue.pop_back();
        playerQueue.pop_back();

        pendingLobby = newLobby;
        activelobbies.push_back(newLobby);
        return "1";


    }
    return "0";
}

bool QuickGame::isntInQueue(const std::string& username) {
    for (const auto& player : playerQueue) {
        if (player.username == username) {
            return false; // Player is already in the queue
        }
    }
    return true; // Player is not in the queue
}

std::string QuickGame::removeFromQueue(const std::string& username) {
    for (auto it = playerQueue.begin(); it != playerQueue.end(); ++it) {
        if (it->username == username) {
            playerQueue.erase(it);
            break; // Assuming usernames are unique
        }
    }
    return "0";
}

bool QuickGame::isPlayerInAnyLobby(const std::string& username) {
    for (GameLobby* lobby : activelobbies) {
        if (lobby->hasPlayer(username)) {
            return true; // Player found in this lobby
        }
    }
    return false; // Player not found in any lobby
}