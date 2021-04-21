cmake_minimum_required(VERSION 3.10)

project(cursive)

include(cmake/FindCursesW.cmake)

if(CURSES_FOUND)
    message(STATUS "ncursesw console enabled: ${CURSES_INCLUDE_PATH}")
    include_directories(${CURSES_INCLUDE_PATH})
else()
    message(FATAL_ERROR STATUS "ncurses not found!")
endif()

add_library(${PROJECT_NAME} SHARED cursive.cpp ${CMAKE_SOURCE_DIR}/theme_impl.cpp)
target_link_libraries(${PROJECT_NAME} pthread dl)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib/cogui/themes)
