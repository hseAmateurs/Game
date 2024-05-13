project(Client)


add_executable(Client
        main.cpp
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
        encryption/map_encryption.cpp
        encryption/map_encryption.h
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