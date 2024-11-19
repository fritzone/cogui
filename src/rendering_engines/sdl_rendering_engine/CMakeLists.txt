cmake_minimum_required(VERSION 3.10)

project(sdl_rendering_engine)


find_package(SDL2 REQUIRED)


add_library(${PROJECT_NAME} STATIC sdl_rendering_engine.cpp
sdl_rendering_engine.h
)

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} cogui ${SDL2_LIBRARIES})
