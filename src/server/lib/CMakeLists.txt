
add_library (server_lib SHARED "")

set (CMAKE_POSITION_INDEPENDENT_CODE ON)

target_sources (server_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Server.cc
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/clients
	)

target_include_directories (server_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_link_libraries (server_lib PUBLIC
	echo-server-interface-library
	core_lib
	net_lib
	)

if (${ENABLE_TESTS})
	target_link_libraries (server_lib PUBLIC
		echo-server-interface-test-library
		)
endif ()
