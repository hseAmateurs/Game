#include "controller.h"
#include "client.h"


int main(){
    Client client("127.0.0.1", 8080); // Создаем клиента, подключающегося к localhost:8080
    //Client client("192.168.201.60", 8080); // для подключения к другому устройству через локальную сеть нужно ввести ipv4 адапрера беспроводной сети(cmd: ipconfig)
    client.start(); // Запускаем клиент

    Controller controller;
    controller.run();
}