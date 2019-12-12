# CMakeLists.txt
# Date: 2019-12-15
# Author: Dr. Ruggero Vasile (ruleva1983@gmail.com)

project ( ProPath )

cmake_minimum_required ( VERSION 3.5 )

option (BUILD_TESTS "Enable to build tests" ON)
option (BUILD_EXAMPLES "Enable to build examples" OFF)

add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

find_package ( Boost )

include_directories ( SYSTEM ${Boost_INCLUDE_DIRS} )

set(src/containers.cpp
    src/utils.cpp
    src/dijkstra.cpp
    )

include_directories(include)
include_directories(third-party)


if ( ${BUILD_TESTS} )
    add_subdirectory ( test )
endif ()

if ( ${BUILD_EXAMPLES} )
	add_subdirectory(applications)
endif ()


