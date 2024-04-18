project(Client)


add_executable(Client
        main.cpp
        ../common.h
        ../network/socket.h
        ../network/socket.cpp
        client.h
        client.cpp
)




# Для платформы windows используем статическую библиотеку sfml
if (WIN32)
    #target_link_libraries(Client Ws2_32)
    set(SFML_ROOT ${CMAKE_SOURCE_DIR}/sfml)
    set(SFML_STATIC_LIBRARIES TRUE)
    #target_link_options(Client PRIVATE -mwindows)
endif ()

# Поиск компонентов библиотеки
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

if (SFML_FOUND)
    # Добавление headers
    target_include_directories(Client PRIVATE ${SFML_INCLUDE_DIR})
    # Линковка библиотек
    if (WIN32)
        target_link_libraries(Client PRIVATE m sfml-graphics sfml-window sfml-system Ws2_32)
    else ()
        target_link_libraries(Client PRIVATE m sfml-graphics sfml-window sfml-system)
    endif ()
endif ()