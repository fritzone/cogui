cmake_minimum_required(VERSION 3.1)

project(cogui)

include(cmake/cogui.cmake)
include(cmake/JSONParser.cmake)

SUBDIRLIST(themes ${CMAKE_SOURCE_DIR}/themes)
set(theme "" CACHE STRING "The theme used to run the application")
set_property(CACHE theme PROPERTY STRINGS ${themes})

set(THEMES_SOURCES "" CACHE STRING "All the source files for all the themes")

FOREACH(theme ${themes})
	message("Theme found: ${theme}")
	add_subdirectory(themes/${theme})
	file(READ ${CMAKE_SOURCE_DIR}/themes/${theme}/theme.json ${theme}_json_content)
	sbeParseJson(${theme}_json ${theme}_json_content)

	foreach(var ${${theme}_json})
	    message("${var} = ${${var}}")
	endforeach()

	file(GLOB ${theme}_SRC
    	"${CMAKE_SOURCE_DIR}/themes/${theme}/*.h"
    	"${CMAKE_SOURCE_DIR}/themes/${theme}/*.cpp"
	)

	list(APPEND THEMES_SOURCES ${theme}_SRC)

ENDFOREACH()

message("All themes: ${themes}")

set (CMAKE_CXX_STANDARD 17)

set(PROJECT_SOURCES
    cogui.cpp
    window.cpp desktop.cpp 
    ${THEMES_SOUCES}
    graphics.cpp application.cpp events.cpp mouse.cpp xterm_input.cpp gpm_input.cpp arguments.cpp
    control.cpp button.cpp container.cpp layout.cpp menu.cpp checkbox.cpp
    logstream.cpp
)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} main.cpp)
target_link_libraries(${PROJECT_NAME} ${CURSES_NCURSESW_LIBRARY} pthread dl gpm)


