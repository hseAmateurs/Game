project(Server)

add_executable(Server
        main.cpp
        network/server.h
        network/server.cpp
        dataBase/playerDatabase.h
        dataBase/playerDatabase.cpp
        contreller/controller.cpp
)

if (WIN32)
target_link_libraries(Server Ws2_32)
endif ()