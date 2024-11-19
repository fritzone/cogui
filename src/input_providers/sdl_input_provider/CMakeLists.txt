cmake_minimum_required(VERSION 3.10)

project(sdl_input_provider)

add_library(${PROJECT_NAME} STATIC sdl_input_provider.cpp)
target_link_libraries(${PROJECT_NAME} SDL2)
