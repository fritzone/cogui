cmake_minimum_required(VERSION 3.10)

include(cmake/FindGPM.cmake)
if(NOT ${LIBGPM_FOUND})
    message(FATAL_ERROR "libgpm was not found, it is required for mouse input")
endif()

project(gpm_input_provider)

add_library(${PROJECT_NAME} SHARED gpm_input_provider.cpp)
target_link_libraries(${PROJECT_NAME} gpm pthread ncursesw)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib/cogui/input_providers)
