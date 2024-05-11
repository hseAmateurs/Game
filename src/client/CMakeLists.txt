project(Client)


include_directories(menu)

add_executable(Client
        menu/menu.h
        menu/menuManager.h
        menu/menuButton.h
        menu/textField.h
        menu/authorizationMenu.h
        menu/registrationMenu.h
        menu/startMenu.h
        menu/mainMenu.h
        menu/controller.h
        menu/controller.cpp
        menu/statisticsMenu.h
        menu/friendEntry.h
        menu/friendsMenu.h
        menu/quickplayMenu.h
        menu/gameScreen.h
        menu/createjoinMenu.h
        menu/lobbyMenu.h
        menu/awaitingMenu.h
        menu/invitationMenu.h
        main.cpp
        ../common.h

        client.h
        client.cpp
        menu/menu.cpp
        menu/menuManager.cpp
        menu/menuButton.cpp
        menu/textField.cpp
        menu/authorizationMenu.cpp
        menu/registrationMenu.cpp
        menu/startMenu.cpp
        menu/mainMenu.cpp
        menu/statisticsMenu.cpp
        menu/friendEntry.cpp
        menu/friendsMenu.cpp
        menu/quickplayMenu.cpp
        menu/gameScreen.cpp
        menu/createjoinMenu.cpp
        menu/lobbyMenu.cpp
        menu/awaitingMenu.cpp
        menu/invitationMenu.cpp
        utils/settings.h
        map/positions.h
        map/positions.cpp
        map/hexagon.h
        map/hexagon.cpp
        map/map.h
        map/map.cpp
        utils/globalFunctions.cpp
        utils/globalFunctions.h
        heroes/Hero.cpp
        heroes/RangeHit.cpp
        utils/overloads.cpp
        utils/overloads.h
        core/assets.cpp
        core/assets.h
        core/field.cpp
        core/field.h
        utils/secondOrderDynamics.h
        map/tree.cpp
        map/tree.h
        heroes/FrostWave.cpp
        heroes/IceSpikes.cpp
        heroes/circleShape.cpp
        heroes/Blizzard.cpp
        heroes/rectangleShape.cpp
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
    if (WIN32)
        target_link_libraries(Client PRIVATE m sfml-graphics sfml-window sfml-system Ws2_32)
    else ()
        target_link_libraries(Client PRIVATE m sfml-graphics sfml-window sfml-system)
    endif ()
endif ()