#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <vector>
#include <string>
#include <sstream>
#include "../dataBase/playerDatabase.h"
#include "../gameLobby/quickGame.h"


class Controller {
public:
    Controller(PlayerDatabase& database, std::vector<GameLobby*> &activelobbies, QuickGame &quickGameQueue) : database(database),  quickGameQueue(quickGameQueue), activelobbies(activelobbies) {}
    std::string handleRequest(const std::string& request, int &client_socket, bool enteringLobby, GameLobby *clientLobby);

private:
    struct Invite{

        std::string host, friend1, friend2;
        GameLobby *lobby = nullptr;
        bool connection1 = false, connection2 = false;
        int sock1, sock2;
    };

    PlayerDatabase& database;
    int requestCode;
    std::vector<std::string> params;
    QuickGame &quickGameQueue;
    std::vector<GameLobby*> &activelobbies;
    std::vector<Invite> invites;



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

    std::string handleStartFriendLobby(int &client_socket, bool enteringLobby,GameLobby *client_lobby);

    std::string handleWaitingFriendLobby(int &client_socket, bool enteringLobby, GameLobby *client_lobby);

    std::string handleButtonPress(int &client_socket, GameLobby *client_lobby);

    std::string handleMouseAndButtonPress(int &client_socket, GameLobby *client_lobby);

    std::string handleMousePress(int &client_socket, GameLobby *client_lobby);

    std::string handleGameRequest(int &socket, GameLobby *pLobby);
};


#endif //GAME_CONTROLLER_H
