cmake_minimum_required(VERSION 3.10)

project(ncurses_rendering_engine)

include(cmake/FindCursesW.cmake)

if(CURSES_FOUND)
    message(STATUS "graphics engine: ncursesw console enabled: ${CURSES_INCLUDE_PATH}")
    include_directories(${CURSES_INCLUDE_PATH})
else()
    message(FATAL_ERROR STATUS "ncurses not found!")
endif()

add_library(${PROJECT_NAME} STATIC ncurses_rendering_engine.cpp
    frame.cpp
    frame.h)
target_link_libraries(${PROJECT_NAME} ${CURSES_NCURSESW_LIBRARY} pthread dl cogui cogui_mouse cogui_logger)
