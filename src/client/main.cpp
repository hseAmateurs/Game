#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    // Создаем сокет
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    // Задаем адрес сервера
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    // Подключаемся к серверу
    if (connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Ошибка подключения к серверу" << std::endl;
        return 1;
    }

    while (true) {
        // Вводим сообщение
        std::string message;
        std::cout << "Введите сообщение: ";
        std::getline(std::cin, message);

        // Отправляем сообщение серверу
        send(client_fd, message.c_str(), message.length(), 0);

        // Получаем ответ от сервера
        char buffer[1024] = {0};
        int bytes_read = read(client_fd, buffer, 1024);
        if (bytes_read == -1) {
            std::cerr << "Ошибка чтения сообщения" << std::endl;
            break;
        }

        // Выводим ответ
        std::cout << "Ответ сервера: " << buffer << std::endl;
    }

    // Закрываем сокет
    close(client_fd);

    return 0;
}