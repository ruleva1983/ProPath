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
    Mat_prod_access product_mats(access_mats);
    
    //Complete test

}

 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


