
add_executable (server)

target_sources (server PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cc
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/lib
	)

target_include_directories (server PUBLIC
	)

target_link_libraries (server PUBLIC
	echo-server-interface-library
	core_lib
	server_lib
	)
