project(Server)

add_executable(Server
        main.cpp
        ../common.h
)

if (WIN32)
target_link_libraries(Server Ws2_32)
endif ()