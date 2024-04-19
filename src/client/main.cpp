#include "client.h"

int main() {
    Client client("127.0.0.1", 8080); // Создаем клиента, подключающегося к localhost:8080
    client.start(); // Запускаем клиент

    char message[1024]={0};

    while (true) {
        //char buffer[1024]={0};
        printf("Enter message: ");
        fgets(message, 1024, stdin);

        client.sendMessage(message);
        printf("Message sent\n");

        std::string buffer = client.getMessage();
        std::cout<<"Server: "<<buffer<<"\n";
    }


    return 0;
}