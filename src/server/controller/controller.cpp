#include "controller.h"
//#include "../gameLobby/utils.cpp"

std::string Controller::handleRequest(const std::string& request, int &client_socket, bool enteringLobby, GameLobby *clientLobby) {
    parseRequest(request);

    // Call the appropriate handler based on the request code
    switch (requestCode) {
        case 100: return handleAuthorization();
        case 200: return handleRegistration();
        case 301: return handleGetStatistics();
        case 302: return handleUpdateStatistics();
        case 401: return handleGetFriends();
        case 402: return handleAddFriend();
        case 501: return handleStartQuickSearch(client_socket, enteringLobby);
        case 502: return handleStopQuickSearch();
        case 601: return handleGameCommand(client_socket, clientLobby);
        default: return "UNKNOWN_REQUEST";
    }
}


void Controller::parseRequest(const std::string& request) {
    std::stringstream ss(request);
    ss >> requestCode;

    // Extract parameters
    std::string param;
    params.clear();
    while (ss >> param) {
        params.push_back(param);
    }
}


std::string Controller::handleAuthorization() {
    if (params.size() < 2) {
        return "WRONG_REQUEST";
    }

    std::string login = params[0];
    std::string password = params[1];

    int result = database.findUser(login, password);
    switch (result) {
        case 0: return "0"; // OK
        case 1: return "1"; // WRONG_PASSWORD
        case -1: return "2"; // NO_LOGIN
        default: return "UNKNOWN_ERROR";
    }
}

std::string Controller::handleRegistration() {
    if (params.size() < 2) {
        return "WRONG_REQUEST";
    }

    std::string login = params[0];
    std::string password = params[1];

    if (database.findLogin(login) != -1) {
        return "1"; // LOGIN_EXIST
    }

    database.addPlayer(login, password);
    return "0"; // OK
}

std::string Controller::handleGetStatistics() {
    if (params.size() < 1) {
        return "WRONG_REQUEST";
    }

    std::string login = params[0];
    auto [deaths, kills, gameCounter] = database.getStats(login);

    // Build the response string
    std::ostringstream oss;
    oss << deaths <<  " " << kills << " " << gameCounter;

    if (deaths == -1 && kills == -1 && gameCounter == -1) {
        return "1"; // SMT_WENT_WRONG
    }

    return oss.str();
}

std::string Controller::handleUpdateStatistics() {
    if (params.size() < 3) {
        return "WRONG_REQUEST";
    }

    std::string login = params[0];
    std::cout<<params[1];
    int newDeaths = std::stoi(params[1]);
    int newKills = std::stoi(params[2]);

    database.updateStats(login, newDeaths, newKills);
    return "0"; // OK
}

std::string Controller::handleGetFriends() {
    if (params.size() < 1) {
        return "WRONG_REQUEST";
    }

    std::string login = params[0];
    std::vector<std::string> friends = database.getFriends(login);

    std::ostringstream oss;
    for (const std::string& friendLogin : friends) {
        oss << friendLogin << " ";
    }

    if (friends.empty()) {
        return "0"; // SMT_WENT_WRONG
    }

    return oss.str();
}

std::string Controller::handleAddFriend() {
    if (params.size() < 2) {
        return "WRONG_REQUEST";
    }

    std::string login = params[0];
    std::string friendLogin = params[1];

    if (database.findLogin(friendLogin) != -1) {
        bool isntFriendFlag = true;
        for (auto f : database.getFriends(login)){
            if (f == friendLogin){
                isntFriendFlag = false;
                return "1"; //is friend now
            }
        }
        if (isntFriendFlag) {
            database.addFriend(login, friendLogin);
            database.addFriend(friendLogin, login);
            return "0";// OK
        }
    }
    return "2"; // login doesnt exist
}



std::string Controller::handleStartQuickSearch(int &client_socket, bool enteringLobby) {
    if (params.size() < 1) {
        return "WRONG_REQUEST";
    }
    std::string login = params[0];
    if (quickGameQueue.isPlayerInAnyLobby(params[0])){
        enteringLobby = true;
        return "1";    // Return a message indicating that the search has started
    }else if (quickGameQueue.isntInQueue(login)) {
        return quickGameQueue.addToQueue(login, client_socket);
    } else if (!quickGameQueue.isPlayerInAnyLobby(params[0])){
        return quickGameQueue.matchmake(params[0]);
    }

    return "SMTH_WENT_WRONG";
}

std::string Controller::handleStopQuickSearch() {
    if (params.size() < 1) {
        return "WRONG_REQUEST";
    }
    std::string login = params[0];
    quickGameQueue.removeFromQueue(login);
    // Return a message indicating that the search has stopped
    return "0";
}



std::string Controller::handleGameCommand(int clientSocket, GameLobby *clientLobby) {
    clientLobby->test=atoi(params[2].c_str());
    return "0";
}
