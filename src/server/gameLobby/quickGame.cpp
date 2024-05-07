#include "quickGame.h"
#include "gameLobby.h"


std::string QuickGame::addToQueue(const std::string& username, int clientSocket) {
    PlayerInfo player;
    player.username = username;
    player.clientSocket = clientSocket;
    playerQueue.push_back(player);
    return "0";//success
}

void QuickGame::loadGameLobby() {
    if (playerQueue.size() >= 2) { // Assuming 2 players for a game
        // Create a new GameLobby instance
        GameLobby* newLobby = new GameLobby();
        activelobbies.push_back(newLobby);

        // Add the first two players from the queue to the lobby
        for (int i = 0; i < 2; ++i) {
            newLobby->addPlayer(playerQueue[i].username, playerQueue[i].clientSocket);
            playerQueue.erase(playerQueue.begin());
        }

        // Notify players that the lobby has been created
        newLobby->notifyPlayers("Lobby created! Waiting for game to start...");
    }
}

std::string QuickGame::matchmake(const std::string login) {

    if (playerQueue.size() >= 3) { // Check if we have enough players for a lobby
        // Create a new GameLobby instance
        GameLobby* newLobby = new GameLobby();

        // Add the first 3 players to the lobby
        for (int i = 0; i < 3; ++i) {
            newLobby->addPlayer(playerQueue[i].username, playerQueue[i].clientSocket);
        }

        // Remove those players from the queue
        playerQueue.erase(playerQueue.begin(), playerQueue.begin() + 3);
        lobbyCreatedFlag = true;
        pendingLobby = newLobby;
        // Notify players about the new lobby (implementation in GameLobby)
        //newLobby->notifyPlayers("abc");
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
    //matchmake(username);
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