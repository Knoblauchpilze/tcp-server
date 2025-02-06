
add_library (core_lib SHARED "")

set (CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/log
	)

target_sources (core_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Uuid.cc
	${CMAKE_CURRENT_SOURCE_DIR}/CoreException.cc
	${CMAKE_CURRENT_SOURCE_DIR}/SafetyNet.cc
	${CMAKE_CURRENT_SOURCE_DIR}/CoreObject.cc
	${CMAKE_CURRENT_SOURCE_DIR}/RNG.cc
	)

target_link_libraries (core_lib
	)

target_include_directories (core_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)
