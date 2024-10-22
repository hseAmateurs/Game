#ifndef CLIENT_H
#define CLIENT_H

#include "../common.h"
#include <iostream>

class Client {
public:
    Client(const std::string& address, int port);
    ~Client();
    void start();
    bool sendMessage(const char* message);
    std::string getMessage();

private:
    std::string address;
    int port;
    int sock;
};

#endif // CLIENT_H