
add_executable (unitTests)

target_sources (unitTests PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cc
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/core
	)

target_include_directories (unitTests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_link_libraries (unitTests
	core_lib
	GTest::gtest_main
	echo-server-interface-test-library
	)
