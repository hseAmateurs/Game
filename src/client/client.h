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
    void setLogin(std::string log){login=log;};
    std::string getLogin(){return login;};
    void setDeaths(std::string num){deaths=num;};
    void setKills(std::string num){kills=num;};
    void setGamecount(std::string num){gamecount=num;};
    std::string getDeaths(){return deaths;};
    std::string getKills(){return kills;};
    std::string getGamecount(){return gamecount;};

private:
    std::string address;
    int port;
    int sock;
    std::string login;
    std::string deaths; // во время игры можно менять эти поля, а не отправлять сразу изменения на сервер
    std::string kills; // главное НЕ ЗАБЫТЬ ПОТОМ ОБ ЭТОМ РАССКАЗАТЬ СЕРВЕРУ!!!!!!!
    std::string gamecount;
};

#endif // CLIENT_H