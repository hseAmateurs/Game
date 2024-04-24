#ifndef SERVER_H
#define SERVER_H

#include "../../common.h"
#include <thread>
#include "../dataBase/playerDatabase.h"

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

};

#endif // SERVER_H