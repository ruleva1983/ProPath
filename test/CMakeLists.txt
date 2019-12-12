
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#target_link_libraries(gtest gmock gmock_main)

add_executable(test_dijkstra test_dijkstra.cpp)
target_link_libraries(test_dijkstra ${GTEST_LIBRARIES} pthread)
