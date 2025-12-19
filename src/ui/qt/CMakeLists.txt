target_sources(${PROJECT_NAME}
        PRIVATE
                qt_game_map.cpp
                qt_ui_factory.cpp
                main_window.cpp
                qt_ui_object.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_subdirectory(qt_objects)
