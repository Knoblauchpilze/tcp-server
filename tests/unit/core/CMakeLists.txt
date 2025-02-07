
target_include_directories (tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_sources (server_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/UuidTest.cc
	)
