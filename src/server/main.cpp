#include "../common.h"
#include <cstdio>   // printf, perror
#include <cstdlib>  // exit, malloc
#include <cstring>  // strlen
#include <thread>   // std::thread

#define PORT 8080

#define PORT 8080

void handle_client(int client_socket) {
    char buffer[1024] = {0};

    while (true) {
        int valread = read(client_socket, buffer, 1024);
        if (valread <= 0) {
            break; // Client disconnected
        }
        printf("Client %d: %s\n", client_socket, buffer);
        send(client_socket, "Hello from server", strlen("Hello from server"), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }
#endif

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        std::thread client_thread(handle_client, new_socket);
        client_thread.detach();
    }

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}