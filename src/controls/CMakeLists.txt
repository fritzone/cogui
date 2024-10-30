project(cogui_controls)

set(PROJECT_SOURCES
        ${CMAKE_BINARY_DIR}/themes.cpp
        ${CMAKE_BINARY_DIR}/rendering_engines.cpp
        ${CMAKE_BINARY_DIR}/input_providers.cpp
        ${CMAKE_BINARY_DIR}/extension_manager.cpp

    cogui.cpp dynamic_library.cpp
    window.cpp desktop.cpp
    application.cpp events.cpp arguments.cpp action.cpp menubar.cpp key.cpp
    control.cpp button.cpp container.cpp layout.cpp menu.cpp checkbox.cpp radiobutton.cpp radiobutton_group.cpp scrollbar.cpp
)


add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)

message("all extensions: ${ALL_THEMES} ${ALL_RENDERING_ENGINES} ${ALL_INPUT_PROVIDERS}")

target_link_libraries(${PROJECT_NAME} dl cogui_mouse cogui_logger ${ALL_THEMES} ${ALL_RENDERING_ENGINES} ${ALL_INPUT_PROVIDERS})
