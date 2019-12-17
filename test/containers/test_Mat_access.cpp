#include <gtest/gtest.h>
#include <math.h>
#include <vector>
#include <string>
#include "containers.hpp"
 
using namespace std;
 

TEST(Dimensions, Dimensions){

    vector<string> file_names;
    file_names.push_back("../../../test/containers/test_data/mat_smart_1.dat");
    file_names.push_back("../../../test/containers/test_data/mat_smart_2.dat");
    
    Mat_vector vector_of_mats(6, file_names, "smart"); 
    Mat_access access_mats(vector_of_mats, 0);
    
    ASSERT_EQ(access_mats.dimension(), vector_of_mats.dimension());
    ASSERT_EQ(access_mats.steps(), vector_of_mats.steps());
    
    
    vector<string> file_names2;
    file_names2.push_back("../../../test/containers/test_data/mat_standard_1.dat");
    
    Mat_vector vector_of_mats2(3, file_names2, "standard"); 
    Mat_access access_mats2(vector_of_mats2, 0);
    
    ASSERT_EQ(access_mats2.dimension(), vector_of_mats2.dimension());
    ASSERT_EQ(access_mats2.steps(), vector_of_mats2.steps());
    
}

// Add a test with the threshold parameter in place
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

