project(cogui_controls VERSION 0.0.1 LANGUAGES CXX)

set(PROJECT_SOURCES
    ${CMAKE_BINARY_DIR}/themes.cpp
    ${CMAKE_BINARY_DIR}/rendering_engines.cpp
    ${CMAKE_BINARY_DIR}/input_providers.cpp
    ${CMAKE_BINARY_DIR}/extension_manager.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/cogui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dynamic_library.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/desktop.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/events.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/arguments.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/action.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/menubar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/button.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/container.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/checkbox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/radiobutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/radiobutton_group.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scrollbar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/theme_impl.cpp

    ${CMAKE_SOURCE_DIR}/inc/action.h
    ${CMAKE_SOURCE_DIR}/inc/application.h
    ${CMAKE_SOURCE_DIR}/inc/arguments.h
    ${CMAKE_SOURCE_DIR}/inc/button.h
    ${CMAKE_SOURCE_DIR}/inc/checkable.h
    ${CMAKE_SOURCE_DIR}/inc/checkbox.h
    ${CMAKE_SOURCE_DIR}/inc/clickable.h
    ${CMAKE_SOURCE_DIR}/inc/cogui.h
    ${CMAKE_SOURCE_DIR}/inc/color.h
    ${CMAKE_SOURCE_DIR}/inc/container.h
    ${CMAKE_SOURCE_DIR}/inc/control_creator.h
    ${CMAKE_SOURCE_DIR}/inc/control_grouper.h
    ${CMAKE_SOURCE_DIR}/inc/control.h
    ${CMAKE_SOURCE_DIR}/inc/desktop.h
    ${CMAKE_SOURCE_DIR}/inc/dynamic_library.h
    ${CMAKE_SOURCE_DIR}/inc/events.h
    ${CMAKE_SOURCE_DIR}/inc/extension.h
    ${CMAKE_SOURCE_DIR}/inc/extension_manager.h
    ${CMAKE_SOURCE_DIR}/inc/factory.h
    ${CMAKE_SOURCE_DIR}/inc/input_provider.h
    ${CMAKE_SOURCE_DIR}/inc/key.h
    ${CMAKE_SOURCE_DIR}/inc/layout.h
    ${CMAKE_SOURCE_DIR}/inc/log.h
    ${CMAKE_SOURCE_DIR}/inc/logstream.h
    ${CMAKE_SOURCE_DIR}/inc/logstreamhelper.h
    ${CMAKE_SOURCE_DIR}/inc/logtypes.h
    ${CMAKE_SOURCE_DIR}/inc/menubar.h
    ${CMAKE_SOURCE_DIR}/inc/menu.h
    ${CMAKE_SOURCE_DIR}/inc/miso.h
    ${CMAKE_SOURCE_DIR}/inc/mouse.h
    ${CMAKE_SOURCE_DIR}/inc/named_type.h
    ${CMAKE_SOURCE_DIR}/inc/overload_impl.h
    ${CMAKE_SOURCE_DIR}/inc/radiobutton_group.h
    ${CMAKE_SOURCE_DIR}/inc/radiobutton.h
    ${CMAKE_SOURCE_DIR}/inc/rect.h
    ${CMAKE_SOURCE_DIR}/inc/rendering_engine.h
    ${CMAKE_SOURCE_DIR}/inc/scrollbar.h
    ${CMAKE_SOURCE_DIR}/inc/state_changer.h
    ${CMAKE_SOURCE_DIR}/inc/themeable.h
    ${CMAKE_SOURCE_DIR}/inc/theme.h
    ${CMAKE_SOURCE_DIR}/inc/timer.h
    ${CMAKE_SOURCE_DIR}/inc/tuple_iterator.h
    ${CMAKE_SOURCE_DIR}/inc/utils.h
    ${CMAKE_SOURCE_DIR}/inc/window.h
    ${CMAKE_SOURCE_DIR}/inc/string_type.h
    ${CMAKE_SOURCE_DIR}/inc/positionable.h
    ${CMAKE_SOURCE_DIR}/inc/label.h
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)

message("all extensions: ${ALL_THEMES} ${ALL_RENDERING_ENGINES} ${ALL_INPUT_PROVIDERS}")

target_link_libraries(${PROJECT_NAME} dl 
    cogui_mouse cogui_logger cogui_keyboard
    ${ALL_THEMES} ${ALL_RENDERING_ENGINES} ${ALL_INPUT_PROVIDERS}
)
