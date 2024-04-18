#ifndef SERVER_H
#define SERVER_H

#include "../common.h"
#include <thread>

class Server {
public:
    Server(int port);
    ~Server();
    void start();

private:
    void handle_client(int client_socket);
    int port;
    int server_fd;
};

#endif // SERVER_H