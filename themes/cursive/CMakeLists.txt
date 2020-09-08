cmake_minimum_required(VERSION 2.8)

project(cursive)

include(cmake/FindCursesW.cmake)

if(CURSES_FOUND)
    message(STATUS "ncursesw console enabled: ${CURSES_INCLUDE_PATH}")
    include_directories(${CURSES_INCLUDE_PATH})
else()
    message(FATAL_ERROR STATUS "ncurses not found!")
endif()

add_library(${PROJECT_NAME} SHARED cursive.cpp)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib/cogui/themes)