
set(sources ../../src/containers.cpp 
    test_Mat_vector.cpp
    )
    
add_executable(test_Mat_vector  ${sources})
target_link_libraries(test_Mat_vector ${GTEST_LIBRARIES} pthread)
