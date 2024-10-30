cmake_minimum_required(VERSION 3.10)

project(cursive_theme)

include(cmake/FindCursesW.cmake)

if(CURSES_FOUND)
    message(STATUS "ncursesw includes found at: ${CURSES_INCLUDE_PATH}")
    include_directories(${CURSES_INCLUDE_PATH})
else()
    message(FATAL_ERROR STATUS "ncursesw not found! To use the ${PROJECT_NAME} theme you will need to install it.")
endif()

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cursive.cpp
)

target_link_libraries(${PROJECT_NAME} pthread dl)
