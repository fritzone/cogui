cmake_minimum_required(VERSION 2.8)
project(cogui)

set (CMAKE_CXX_STANDARD 17)

add_definitions(-DLOGURU_WITH_STREAMS)

include(FindCursesW.cmake)
if(CURSES_FOUND)
    message(STATUS "ncursesw console enabled: ${CURSES_INCLUDE_PATH}")
    include_directories(${CURSES_INCLUDE_PATH})
else()
    message(STATUS "ncurses not found!")
endif()

set(PROJECT_SOURCES
    loguru.cpp
    cogui.cpp
    window.cpp desktop.cpp theme.cpp graphics.cpp application.cpp events.cpp mouse.cpp xterm_input.cpp gpm_input.cpp
    control.cpp button.cpp container.cpp
)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} main.cpp)
target_link_libraries(${PROJECT_NAME} ${CURSES_NCURSESW_LIBRARY} pthread dl gpm)


