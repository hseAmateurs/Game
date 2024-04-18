#include "client.h"

int main() {
    Client client("127.0.0.1", 8080); // Создаем клиента, подключающегося к localhost:8080
    client.start(); // Запускаем клиент
    return 0;
}