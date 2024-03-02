cmake_minimum_required(VERSION 3.3)
project(P2M)

set(TETWILD_EXTERNAL "${CMAKE_CURRENT_SOURCE_DIR}/extern")

option(ENABLE_TBB    "Enable TBB"    ON)

# TBB
if(ENABLE_TBB AND NOT TARGET tbb::tbb)
	# float_tetwild_download_tbb()

	set(TBB_BUILD_STATIC ON CACHE BOOL " " FORCE)
	set(TBB_BUILD_SHARED OFF CACHE BOOL " " FORCE)
	set(TBB_BUILD_TBBMALLOC OFF CACHE BOOL " " FORCE)
	set(TBB_BUILD_TBBMALLOC_PROXY OFF CACHE BOOL " " FORCE)
	set(TBB_BUILD_TESTS OFF CACHE BOOL " " FORCE)
	set(TBB_NO_DATE ON CACHE BOOL " " FORCE)

	add_subdirectory(${TETWILD_EXTERNAL}/tbb tbb)
	set_target_properties(tbb_static PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES "${TETWILD_EXTERNAL}/tbb/include"
	)
	if(NOT MSVC)
		set_target_properties(tbb_static PROPERTIES
			COMPILE_FLAGS "-Wno-implicit-fallthrough -Wno-missing-field-initializers -Wno-unused-parameter -Wno-keyword-macro"
		)
		set_target_properties(tbb_static PROPERTIES POSITION_INDEPENDENT_CODE ON)
	endif()
	add_library(tbb::tbb ALIAS tbb_static)
endif()

# C++11 threads
find_package(Threads REQUIRED)

include_directories(${TETWILD_EXTERNAL}/eigen)
include_directories(${TETWILD_EXTERNAL}/../src)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src PMSRC)
add_library(p2m STATIC ${PMSRC})
target_link_libraries(p2m PUBLIC tbb::tbb)

add_executable(${PROJECT_NAME} main.cpp)

if(ENABLE_TBB)
	target_link_libraries(${PROJECT_NAME} PUBLIC tbb::tbb p2m)
	target_compile_definitions(${PROJECT_NAME} PUBLIC USE_TBB)
endif()
