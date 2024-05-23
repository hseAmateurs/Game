#include "server.h"
#include "../dataBase/playerDatabase.h"

Server::Server(int port) : port(port), server_fd(0), database("players.txt"), controller(database, activeLobbies, quickGameQueue),
                           quickGameQueue(activeLobbies) {}

Server::~Server() {
    closesock(server_fd);
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

        std::thread client_thread(&Server::handle_client, this, new_socket, std::ref(quickGameQueue), std::ref(activeLobbies));
        client_thread.detach();
    }
}
GameLobby* findLobbyBySocket(const std::vector<GameLobby*>& gameLobbies, int clientSocket) {
    for (const auto& lobby : gameLobbies) {
        if (std::find(lobby->playerSockets.begin(), lobby->playerSockets.end(), clientSocket) != lobby->playerSockets.end()) {
            // Найдено лобби, содержащее заданный сокет
            return lobby; // Приведение const
        }
    }
    // Если не найдено, вернуть nullptr, чтобы обозначить, что лобби не найдено
    return nullptr;
}

void Server::handle_client(int client_socket, QuickGame &quickGameQueue, std::vector<GameLobby*> &activeLobbies) {
    GameLobby *clientLobby = nullptr;
    bool enteringLobby = false;
    while (true) {
        std::string message = getMessage(client_socket);
        if (message.empty()) {
            break; // Client disconnected
        }
        //printf("Client %d: %s\n", client_socket, message.c_str());
        std::string answer = controller.handleRequest(message, client_socket, enteringLobby, clientLobby);
        if (enteringLobby){
            enteringLobby = false;
            clientLobby = findLobbyBySocket(activeLobbies, client_socket); // получаем лобби для игрока
        }
        if (!quickGameQueue.lobbyCreatedFlag && answer != "9");
            sendMessage(client_socket, answer.c_str());
        if(clientLobby == NULL)
            clientLobby = findLobbyBySocket(activeLobbies, client_socket);
        if (quickGameQueue.lobbyCreatedFlag && clientLobby) {
            std::thread lobbyThread(&Server::lobbyLoop, this, quickGameQueue.pendingLobby);
            lobbyThread.detach();
            quickGameQueue.lobbyCreatedFlag = false;
            quickGameQueue.pendingLobby = nullptr;
        }
    }
    closesock(client_socket);
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

void Server::lobbyLoop(GameLobby *lobby){ // здесь будет считаться карта и отправляться данные
    std::this_thread::sleep_for(std::chrono::seconds(5));

    while (true) {
        lobby->gameLoop();
        for (auto client_socket: lobby->playerSockets) {
            char *mesage;// = lobby->encrypter.encryptHexs(lobby.);
            //std::cout<<mesage<<"\n";
            //sendMessage(client_socket, mesage);//std::to_string(lobby->test).c_str());
            std::this_thread::sleep_for(std::chrono::milliseconds(16));//sleep before sent
        };
    }
}