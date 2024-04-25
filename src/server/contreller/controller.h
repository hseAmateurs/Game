#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <vector>
#include <string>
#include <sstream>
#include "../dataBase/playerDatabase.h"

class Controller {
public:
    Controller(PlayerDatabase& database) : database(database) {}

    std::string handleRequest(const std::string& request);

private:
    PlayerDatabase& database;
    int requestCode;
    std::vector<std::string> params;

    void parseRequest(const std::string& request);

    std::string handleAuthorization();

    std::string handleRegistration();

    std::string handleGetStatistics();

    std::string handleUpdateStatistics();

    std::string handleGetFriends();

    std::string handleAddFriend();
};


#endif //GAME_CONTROLLER_H
