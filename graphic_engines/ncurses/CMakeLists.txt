cmake_minimum_required(VERSION 2.8)

project(ncurses_engine)

include(cmake/FindCursesW.cmake)

if(CURSES_FOUND)
    message(STATUS "graphics engine: ncursesw console enabled: ${CURSES_INCLUDE_PATH}")
    include_directories(${CURSES_INCLUDE_PATH})
else()
    message(FATAL_ERROR STATUS "ncurses not found!")
endif()

add_library(${PROJECT_NAME} SHARED ncurses_engine.cpp)
target_link_libraries(${PROJECT_NAME} ${CURSES_NCURSESW_LIBRARY} pthread dl gpm)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib/cogui/graphic_engines)
