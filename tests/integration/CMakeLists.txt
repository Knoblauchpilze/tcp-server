
add_executable (integrationTests)

target_sources (integrationTests PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cc
	)

target_include_directories (integrationTests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_link_libraries (integrationTests
	core_lib
	GTest::gtest_main
	echo-server-interface-test-library
	)
