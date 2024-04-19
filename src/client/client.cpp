#include "client.h"

Client::Client(const std::string& address, int port)
        : address(address), port(port), sock(0) {}

Client::~Client() {
    close(sock);
#ifdef _WIN32
    WSACleanup();
#endif
}

void Client::start() {
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char message[1024];

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return;
    }
#endif

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return;
    }

//    while (true) {
//        printf("Enter message: ");
//        fgets(message, 1024, stdin);
//
//        send(sock, message, strlen(message), 0);
//        printf("Message sent\n");
//
//        int valread = recv(sock, buffer, 1024, 0);
//        printf("Server: %s\n", buffer);
//    }
}


bool Client::sendMessage(const char* message) {
    int bytes_sent = send(sock, message, strlen(message), 0);
    return bytes_sent > 0;
}

std::string Client::getMessage() {
    char buffer[1024] = {0};
    int bytes_received = recv(sock, buffer, 1024, 0);
    if (bytes_received <= 0) {
        return "";
    }
    return std::string(buffer, bytes_received);
}