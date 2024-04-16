cmake_minimum_required(VERSION 3.26)
project(Game)

set(CMAKE_CXX_STANDARD 17)

# Добавляем подпроекты Server и Client
add_subdirectory(src/server)
add_subdirectory(src/client)

# Для платформы macOS используем open
if (APPLE)
    set(OPEN_COMMAND open)
endif ()

# Создаем цель для запуска обоих приложений

if (APPLE)
add_custom_target(both
        COMMAND ${OPEN_COMMAND} $<TARGET_FILE:Server>
        COMMAND ${OPEN_COMMAND} $<TARGET_FILE:Client>
        DEPENDS Server Client
)
endif ()

if (WIN32)
add_custom_target(both
        COMMAND start ${OPEN_COMMAND} $<TARGET_FILE:Server>
        COMMAND start ${OPEN_COMMAND} $<TARGET_FILE:Client>
        DEPENDS Server Client
)
endif()
