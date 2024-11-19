cmake_minimum_required(VERSION 3.10)

project(blitmap_theme)

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/blitmap.cpp
)

target_link_libraries(${PROJECT_NAME} SDL2)
