project(Server)

add_executable(Server
        main.cpp
        ../common.h

        network/server.h
        network/server.cpp

        controller/controller.h
        controller/controller.cpp

        dataBase/playerDatabase.h
        dataBase/playerDatabase.cpp
        gameLobby/gameLobby.h
        gameLobby/gameLobby.cpp
        gameLobby/quickGame.h
        gameLobby/quickGame.cpp
        gameLobby/utils.cpp


)

if (WIN32)
target_link_libraries(Server Ws2_32)
endif ()