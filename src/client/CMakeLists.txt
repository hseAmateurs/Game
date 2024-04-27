project(Client)


add_executable(Client
        main.cpp
        settings.h
        map/positions.h
        map/positions.cpp
        map/hexagon.h
        map/hexagon.cpp
        map/map.h
        map/map.cpp
        globalFunctions.cpp
        globalFunctions.h
        heroes/Hero.cpp
        heroes/RangeHit.cpp
        overloads.cpp
        overloads.h
        core/assets.cpp
        core/assets.h
        core/field.cpp
        core/field.h
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