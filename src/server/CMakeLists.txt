project(Server)

add_executable(Server
        main.cpp
        ../common.h
        network/server.h
        network/server.cpp
        dataBase/playerDatabase.h
        dataBase/playerDatabase.cpp
        controller/controller.h
        controller/controller.cpp
        gameLobby/quickGame.h
        gameLobby/quickGame.cpp
)

if (WIN32)
target_link_libraries(Server Ws2_32)
endif ()