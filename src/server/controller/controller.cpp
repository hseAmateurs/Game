#include "controller.h"

std::string Controller::handleRequest(const std::string& request, int &client_socket, bool &enteringLobby, GameLobby *clientLobby) {
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
        case 602: return handleStartFriendLobby(client_socket, enteringLobby, clientLobby); // 602 login friendLogin friendLogin
        case 603: return handleWaitingFriendLobby(client_socket, enteringLobby, clientLobby); // 603 login
        case 701: return handleGameRequest(client_socket, clientLobby);
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

    if (database.findLogin(friendLogin) != -1 && login!=friendLogin) {
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



std::string Controller::handleStartQuickSearch(int &client_socket, bool &enteringLobby) {
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

std::string Controller::handleStartFriendLobby(int &client_socket, bool &enteringLobby, GameLobby *client_lobby) {
    if (params.size() < 3) {
        return "WRONG_REQUEST";
    }
    bool notCreated = true;
    Invite *currInvite;
    for (auto &invite : invites){
        if (invite.host == params[0]){
            notCreated = false;
            currInvite = &invite;
        }
    }
    if (notCreated) {
        Invite invite;
        invite.host = params[0];
        invite.friend1 = params[1];
        invite.friend2 = params[2];

        invites.push_back(invite);
    } else if (currInvite->connection1 && currInvite->connection2) {
        GameLobby* newLobby = new GameLobby();

        newLobby->addPlayer(params[1], client_socket);
        newLobby->addPlayer(currInvite->friend1, currInvite->sock1);
        newLobby->addPlayer(currInvite->friend2, currInvite->sock2);

        currInvite->lobby = newLobby;
        quickGameQueue.lobbyCreatedFlag = true;
        quickGameQueue.pendingLobby = newLobby;

        activelobbies.push_back(newLobby);
        return "1";
    }




    return "0";
}

std::string Controller::handleWaitingFriendLobby(int &client_socket, bool &enteringLobby, GameLobby *client_lobby) {
    if (params.size() < 1) {
        return "WRONG_REQUEST";
    }
    bool isInv = false;
    for (auto &invite: invites){
        if (invite.friend1 == params[0]) {
            invite.connection1 = true;
            invite.sock1 = client_socket;
            isInv = true;
        } else if (invite.friend2 == params[0]) {
            invite.connection2 = true;
            invite.sock2 = client_socket;
            isInv = true;
        }

        if (isInv && invite.lobby != nullptr){
            client_lobby = invite.lobby;
            return "1";
        }
    }
    return "0";
}

std::string Controller::handleGameRequest(int &socket, GameLobby *pLobby) {
    std::string login = params[0];
    int keyPress = std::stoi(params[1]); // 1 or 0
    int keyCode = std::stoi(params[2]);
    int mousePress = std::stoi(params[3]); // 1 or 0
    int mouseCode = std::stoi(params[4]); // 1 - lMb,  2 - rMb
    std::string mousePosStr = params[5];
    int i = 1;
    std::string xStr;
    int signX;
    std::string yStr;
    int signY;

    if (mousePosStr[0] == '+'){
        signX = 1;
    } else {signX = -1;}
    for (i ; mousePosStr[i] != '-' && mousePosStr[i] != '+'; ++i){
        xStr.push_back(mousePosStr[i]);
    }
    if (mousePosStr[i] == '+'){
        signY = 1;
    } else {signY = -1;}
    i++;
    for (i ; i < mousePosStr.length(); ++i){
        yStr.push_back(mousePosStr[i]);
    }

    int x = signX * std::stoi(xStr);
    int y = signY * std::stoi(yStr);

    sf::Vector2i mousePos(x, y); // mouse pos
    std::cout<<login<<" "<<keyPress<<" "<<keyCode<<" "<<mousePress<<" "<<mouseCode<<" "<<mousePos.x<<" "<<mousePos.y<<"\n";



    return "9";
}
