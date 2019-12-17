
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory ( containers )

#add_executable(test_dijkstra test_dijkstra.cpp)
#target_link_libraries(test_dijkstra ${GTEST_LIBRARIES} pthread)
