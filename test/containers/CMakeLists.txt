
set(sources ../../src/containers.cpp 
            ../../src/utils.cpp
    )
    
add_executable(test_Mat_vector  ${sources} test_Mat_vector.cpp)
target_link_libraries(test_Mat_vector ${GTEST_LIBRARIES} pthread)


add_executable(test_Mat_access  ${sources} test_Mat_access.cpp)
target_link_libraries(test_Mat_access ${GTEST_LIBRARIES} pthread)

add_executable(test_Mat_prod_access  ${sources} test_Mat_prod_access.cpp)
target_link_libraries(test_Mat_prod_access ${GTEST_LIBRARIES} pthread)
