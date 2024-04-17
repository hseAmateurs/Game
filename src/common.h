#ifndef COMMON_H
#define COMMON_H

#ifdef _WIN32
#include <winsock2.h> // For Windows sockets
#include <ws2tcpip.h> // For inet_pton
#define close closesocket
typedef int socklen_t;
#else
#include <sys/socket.h> // For Unix sockets
#include <netinet/in.h> // For sockaddr_in
#include <arpa/inet.h> // For inet_pton
#include <unistd.h> // For read, write, close
#include <cstring> // For memset
#define closesocket close
#endif

#endif // COMMON_H