cmake_minimum_required(VERSION 3.27)
project(Game)

set(CMAKE_CXX_STANDARD 14)


set(SERVER
        src/server/main.cpp
)

set(CLIENT
        src/client/main.cpp
)





add_executable(Game
        #${CLIENT}
        ${SERVER}
)



#add_executable(Game
#        src/client/main.cpp
#        src/server/main.cpp)
