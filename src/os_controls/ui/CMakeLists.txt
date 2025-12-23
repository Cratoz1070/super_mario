target_sources(${PROJECT_NAME}
	PRIVATE
	        qt_os_control_settings.cpp
		qt_user_input.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
