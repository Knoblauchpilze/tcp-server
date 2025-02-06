
find_package (GTest REQUIRED)

add_executable (tests)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/unit
	)

target_sources (tests PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cc
	)

target_include_directories (tests PUBLIC
	${GTEST_INCLUDE_DIRS}
	)

target_link_libraries (tests
	core_lib
	${GTEST_LIBRARIES}
	)
