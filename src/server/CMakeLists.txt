project(Server)

add_executable(Server
        main.cpp
        ../common.h
        ../network/socket.h
        ../network/socket.cpp
        server.h
        server.cpp
)

if (WIN32)
target_link_libraries(Server Ws2_32)
endif ()