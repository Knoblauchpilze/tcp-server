
add_executable (tests)

# http://google.github.io/googletest/quickstart-cmake.html
# https://cmake.org/cmake/help/latest/module/FetchContent.html
include (FetchContent)
FetchContent_Declare (
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        v1.15.2
)

FetchContent_MakeAvailable(googletest)

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
	GTest::gtest_main
	)
