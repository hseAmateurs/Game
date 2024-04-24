#include "server.h"
#include "../dataBase/playerDatabase.h"

Server::Server(int port) : port(port), server_fd(0), database("players.txt"), controller(database) {}

Server::~Server() {
    close(server_fd);
#ifdef _WIN32
    WSACleanup();
#endif
}

void Server::start() {
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return;
    }
#endif

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        std::thread client_thread(&Server::handle_client, this, new_socket);
        client_thread.detach();
    }
}

void Server::handle_client(int client_socket) {
    while (true) {
        std::string message = getMessage(client_socket);
        if (message.empty()) {
            break; // Client disconnected
        }
        printf("Client %d: %s\n", client_socket, message.c_str());
        //sendMessage(client_socket, "Hello from server");
        //sendMessage(client_socket, (std::to_string(database.findLogin(message))).c_str());
        sendMessage(client_socket, controller.handleRequest(message).c_str());
    }
    close(client_socket);
}

bool Server::sendMessage(int client_socket, const char* message) {
    int bytes_sent = send(client_socket, message, strlen(message), 0);
    return bytes_sent > 0; // Возвращаем true, если сообщение отправлено
}

std::string Server::getMessage(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, 1024, 0);
    if (bytes_received <= 0) {
        return ""; // Возвращаем пустую строку, если ничего не получено
    }
    return std::string(buffer, bytes_received);
}