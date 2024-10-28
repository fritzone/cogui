project(cogui_controls)


set(PROJECT_SOURCES
        ${CMAKE_BINARY_DIR}/themes.cpp
        ${CMAKE_BINARY_DIR}/rendering_engines.cpp
        ${CMAKE_BINARY_DIR}/input_providers.cpp

    cogui.cpp dynamic_library.cpp
    window.cpp desktop.cpp
    application.cpp events.cpp arguments.cpp action.cpp menubar.cpp key.cpp
    control.cpp button.cpp container.cpp layout.cpp menu.cpp checkbox.cpp radiobutton.cpp radiobutton_group.cpp scrollbar.cpp
)


add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)

target_link_libraries(${PROJECT_NAME} dl cogui_mouse cogui_logger)
