#include "server.h"

int main() {
    Server server(8080); // Создаем сервер на порту 8080
    server.start(); // Запускаем сервер
    return 0;
}