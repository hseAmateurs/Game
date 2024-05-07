#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <vector>
#include <string>
#include <sstream>
#include "../dataBase/playerDatabase.h"
#include "../gameLobby/quickGame.h"
#include "../gameLobby/utils.cpp"


class Controller {
public:
    Controller(PlayerDatabase& database, std::vector<GameLobby*> &activelobbies, QuickGame &quickGameQueue) : database(database),  quickGameQueue(quickGameQueue), activelobbies(activelobbies) {}
    std::string handleRequest(const std::string& request, int &client_socket, bool enteringLobby, GameLobby *clientLobby);

private:
    PlayerDatabase& database;
    int requestCode;
    std::vector<std::string> params;
    QuickGame &quickGameQueue;
    std::vector<GameLobby*> &activelobbies;



    void parseRequest(const std::string& request);

    std::string handleAuthorization();

    std::string handleRegistration();

    std::string handleGetStatistics();

    std::string handleUpdateStatistics();

    std::string handleGetFriends();

    std::string handleAddFriend();

    std::string handleStartQuickSearch(int &client_socket, bool enteringLobby);

    std::string handleStopQuickSearch();

    std::string handleGameCommand(int clientSocket, GameLobby *clientLobby);


};


#endif //GAME_CONTROLLER_H
