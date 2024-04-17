#ifndef COMMON_H
#define COMMON_H

#ifdef _WIN32
#include <winsock2.h> // Windows sockets
#define close closesocket
#else
#include <sys/socket.h> // Unix sockets
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // close
#include <netdb.h>
#define closesocket close
#endif

#endif // COMMON_H