#include <gtest/gtest.h>
#include <math.h>
#include <vector>
#include <string>
#include "containers.hpp"
 
using namespace std;
 


TEST(Read, ReadSmart) { 
    
    vector<string> file_names;
    file_names.push_back("../../../test/containers/test_data/mat_smart_1.dat");
    file_names.push_back("../../../test/containers/test_data/mat_smart_2.dat");
    
    Mat_vector vector_of_mats(6, file_names, "smart"); 
    
    ASSERT_EQ(vector_of_mats.sparse(0).coeff(0,0), 1.2);
    ASSERT_EQ(vector_of_mats.sparse(0).coeff(1,0), 0.0);
    
}
 
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
