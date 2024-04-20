#include "server.h"
#include "dataBase/playerDatabase.h"
#define SERVER


int main() {

#ifdef SERVER
    Server server(8080); // Создаем сервер на порту 8080
    server.start(); // Запускаем сервер
#endif
#ifdef DATABASE
    PlayerDatabase database("players.txt");

    //database.addPlayer("hui", "pizda");
    std::cout<<database.findLogin("biba");

#endif

    return 0;
}