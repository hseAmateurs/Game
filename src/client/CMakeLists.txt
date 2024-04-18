project(Client)


include_directories(menu)

add_executable(Client
        menu/menu.h
        menu/menuButton.h
        menu/textField.h
        menu/authorizationMenu.h
        main.cpp
        menu/menu.cpp
        menu/menuButton.cpp
        menu/textField.cpp
        menu/authorizationMenu.cpp
)




# Для платформы windows используем статическую библиотеку sfml
if (WIN32)
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
    target_link_libraries(Client PRIVATE m sfml-graphics sfml-window sfml-system)
endif ()