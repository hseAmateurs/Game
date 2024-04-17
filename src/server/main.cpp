#include <iostream>
#include <string>
#include <algorithm>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main() {
    // Создаем сокет
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    // Задаем адрес сервера
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Привязываем сокет к адресу
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        std::cerr << "Ошибка привязки сокета" << std::endl;
        return 1;
    }

    // Начинаем прослушивание
    if (listen(server_fd, 3) == -1) {
        std::cerr << "Ошибка прослушивания" << std::endl;
        return 1;
    }

    while (true) {
        // Принимаем соединение
        sockaddr_in client_address;
        socklen_t client_addr_len = sizeof(client_address);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_addr_len);
        if (client_fd == -1) {
            std::cerr << "Ошибка принятия соединения" << std::endl;
            continue;
        }

        // Получаем сообщение от клиента
        char buffer[1024] = {0};
        int bytes_read = read(client_fd, buffer, 1024);
        if (bytes_read == -1) {
            std::cerr << "Ошибка чтения сообщения" << std::endl;
            close(client_fd);
            continue;
        }

        // Переворачиваем сообщение
        std::string message(buffer);
        std::reverse(message.begin(), message.end());
        std::cout<<message<<"\n";

        // Отправляем перевернутое сообщение клиенту
        send(client_fd, message.c_str(), message.length(), 0);

        // Закрываем соединение
        close(client_fd);
    }

    // Закрываем сокет сервера
    close(server_fd);

    return 0;
}