#ifndef SERVER_H
#define SERVER_H

#include "../../common.h"
#include <thread>
#include "../dataBase/playerDatabase.h"
#include "../controller/controller.h"


class Server {
public:
    Server(int port);
    ~Server();
    void start();
    bool sendMessage(int client_socket, const char* message);
    std::string getMessage(int client_socket);

private:
    void handle_client(int client_socket);
    int port;
    int server_fd;
    PlayerDatabase database;
    Controller controller;


};

#endif // SERVER_H