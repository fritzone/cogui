cmake_minimum_required(VERSION 3.20)

project(cogui)

set (CMAKE_CXX_STANDARD 23)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXTRA_DEBUG 0)

include(cmake/cogui.cmake)
include(cmake/JSONParser.cmake)

#
# Checking the platform
#
set(TargetPlatform "" CACHE STRING "The target platform for the build of the library")

if (WIN32)
    message("Running on Win32")
    set(TargetPlatform "windows")
endif (WIN32)

if (UNIX)
    message("Running on Unix*Like. Defaulting to Linux.")
    set(TargetPlatform "linux")
endif (UNIX)

message(STATUS "TargetPlatform='${TargetPlatform}'")

#
# The current timestamp will be placed in the generated files
#
STRING(TIMESTAMP TIMEZ UTC)

#
# The trarget renderer: console or GUI based
#
set(TargetRenderer "console" CACHE STRING "The target renderer for the build of the library")
set(TargetRenderers "console;graphics" CACHE INTERNAL "The possible target engines for the library: console (ncurses) or GUI based (graphics)")
set_property(CACHE TargetRenderer PROPERTY STRINGS ${TargetRenderers})
message(STATUS "TargetRenderer='${TargetRenderer}'")

#
# Generic includes
#
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/inc)

###################################################
#    The core of the project is handled here      #
###################################################

add_subdirectory(src)

#
# Test app
#
add_executable(cogui_ex main.cpp)

target_link_libraries(cogui_ex cogui_controls)
