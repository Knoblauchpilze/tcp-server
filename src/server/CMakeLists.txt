
add_executable (server)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/lib
	)

target_sources (server PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cc
	)

target_include_directories (server PUBLIC
	)

target_link_libraries (server
	core_lib
	server_lib
	)
