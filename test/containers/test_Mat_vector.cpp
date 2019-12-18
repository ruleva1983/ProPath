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


TEST(Read, ReadStandard) { 
    
    vector<string> file_names;
    file_names.push_back("../../../test/containers/test_data/mat_standard_1.dat");
    
    Mat_vector vector_of_mats(3, file_names, "standard"); 
    
    ASSERT_EQ(vector_of_mats.sparse(0).coeff(0,0), 0.0);
    ASSERT_EQ(vector_of_mats.sparse(0).coeff(2,2), -1.0);
    
}

TEST(Dimensions, Size){
    vector<string> file_names;
    file_names.push_back("../../../test/containers/test_data/mat_standard_1.dat");
    
    Mat_vector vector_of_mats(3, file_names, "standard");
    
    ASSERT_EQ(vector_of_mats.size(), 1);
    
    
    vector<string> file_names2;
    file_names2.push_back("../../../test/containers/test_data/mat_smart_1.dat");
    file_names2.push_back("../../../test/containers/test_data/mat_smart_2.dat");
    
    Mat_vector vector_of_mats2(6, file_names2, "smart"); 
    ASSERT_EQ(vector_of_mats2.size(), 2);
    
}

TEST(Dimensions, Dimension){
    vector<string> file_names;
    file_names.push_back("../../../test/containers/test_data/mat_standard_1.dat");
    
    Mat_vector vector_of_mats(3, file_names, "standard");
    
    ASSERT_EQ(vector_of_mats.dimension(), 3);
    
    
    vector<string> file_names2;
    file_names2.push_back("../../../test/containers/test_data/mat_smart_1.dat");
    file_names2.push_back("../../../test/containers/test_data/mat_smart_2.dat");
    
    Mat_vector vector_of_mats2(6, file_names2, "smart"); 
    ASSERT_EQ(vector_of_mats2.dimension(), 6);
    
}

TEST(Subsetting,  Partial){
    vector<string> file_names;
    file_names.push_back("../../../test/containers/test_data/mat_smart_1.dat");
    file_names.push_back("../../../test/containers/test_data/mat_smart_2.dat");
    
    Mat_vector vector_of_mats(6, file_names, "smart"); 
    
    ASSERT_EQ(vector_of_mats.partial(0,2).size(), 2);
    ASSERT_EQ(vector_of_mats.partial(0,1).size(), 1);
    ASSERT_EQ(vector_of_mats.partial(0,0).size(), 0);
    ASSERT_EQ(vector_of_mats.partial(1,1).size(), 0);
    ASSERT_EQ(vector_of_mats.partial(1,2)[0].coeff(0,0), 0.0);
    ASSERT_EQ(vector_of_mats.partial(1,2)[0].coeff(0,1), 1.2);

}

/*
TEST(Subsetting,  Pointer){
    vector<string> file_names;
    file_names.push_back("../../../test/containers/test_data/mat_smart_1.dat");
    file_names.push_back("../../../test/containers/test_data/mat_smart_2.dat");
    
    Mat_vector vector_of_mats(6, file_names, "smart"); 
    
    ASSERT_EQ(vector_of_mats.pointer(0).size(), 2);
    ASSERT_EQ(vector_of_mats.partial(0,1).size(), 1);
    ASSERT_EQ(vector_of_mats.partial(0,0).size(), 0);
    ASSERT_EQ(vector_of_mats.partial(1,1).size(), 0);
    ASSERT_EQ(vector_of_mats.partial(1,2)[0].coeff(0,0), 0.0);
    ASSERT_EQ(vector_of_mats.partial(1,2)[0].coeff(0,1), 1.2);

}
*/

 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
