#include "controller.h"
#include "client.h"

#define SERVER_TEST

#ifdef MENU_TEST
int main(){
    Controller controller;
    controller.run();
}
#endif

#ifdef SERVER_TEST
int main() {
    Client client("127.0.0.1", 8080); // Создаем клиента, подключающегося к localhost:8080
    //Client client("192.168.201.60", 8080); // для подключения к другому устройству через локальную сеть нужно ввести ipv4 адапрера беспроводной сети(cmd: ipconfig)
    client.start(); // Запускаем клиент

    char message[1024]={0};

    while (true) {
        //char buffer[1024]={0};
        printf("Enter message: ");
        fgets(message, 1024, stdin);
        message[strlen(message)-1] = 0;
        client.sendMessage(message);
        printf("Message sent\n");

        std::string buffer = client.getMessage();
        std::cout<<"Server: "<<buffer<<"\n";
        if (message[0] == '/') {
            std::string a = client.getMessage();
            std::cout<<"Server: "<<a<<"\n";
        }
    }


    return 0;
}
#endif