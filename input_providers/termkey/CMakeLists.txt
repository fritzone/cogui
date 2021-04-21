cmake_minimum_required(VERSION 3.10)

include(cmake/FindLibTermkey.cmake)
include(cmake/FindCursesW.cmake)

project(termkey_input_provider)

add_library(${PROJECT_NAME} SHARED termkey_input_provider.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBTERMKEY_LIBRARY} pthread ${CURSES_NCURSESW_LIBRARY})

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib/cogui/input_providers)
