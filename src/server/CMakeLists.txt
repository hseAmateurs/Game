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


        game/utils/settings.h
        game/map/positions.h
        game/map/positions.cpp
        game/map/hexagon.h
        game/map/hexagon.cpp
        game/map/map.h
        game/map/map.cpp
        game/utils/globalFunctions.cpp
        game/utils/globalFunctions.h
        game/heroes/Hero.cpp
        game/heroes/RangeHit.cpp
        game/utils/overloads.cpp
        game/utils/overloads.h
        game/core/assets.cpp
        game/core/assets.h
        game/core/field.cpp
        game/core/field.h
        game/utils/secondOrderDynamics.h
        game/map/tree.cpp
        game/map/tree.h
        game/heroes/FrostWave.cpp
        game/heroes/IceSpikes.cpp
        game/heroes/circleShape.cpp
        game/heroes/Blizzard.cpp
        game/heroes/rectangleShape.cpp


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
    target_include_directories(Server PRIVATE ${SFML_INCLUDE_DIR})
    # Линковка библиотек
    if (WIN32)
        target_link_libraries(Server PRIVATE m sfml-graphics sfml-window sfml-system Ws2_32)
    else ()
        target_link_libraries(Server PRIVATE m sfml-graphics sfml-window sfml-system)
    endif ()
endif ()