#ifndef SERVER_H
#define SERVER_H

#include "../../common.h"
#include <thread>
#include "../dataBase/playerDatabase.h"
#include "../controller/controller.h"
#include <mutex>
#include <chrono>


class Server {
public:
    Server(int port);
    ~Server();
    void start();
    bool sendMessage(int client_socket, const char* message);
    std::string getMessage(int client_socket);
    std::vector<GameLobby*> activeLobbies;
    void lobbyLoop(GameLobby *lobby);
    void createLobbyThread(GameLobby* lobby);
    QuickGame quickGameQueue;

private:
    void handle_client(int client_socket, QuickGame &quickGameQueue, std::vector<GameLobby*> &activeLobbies);
    int port;
    int server_fd;
    PlayerDatabase database;
    Controller controller;
    std::mutex activeLobbiesMutex;
    std::mutex quickGameQueueMutex;






};

#endif // SERVER_H