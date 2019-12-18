#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>
#include <iostream>
#include <vector>

namespace pt = boost::property_tree;

using namespace std;

void parse_json(string filename, int& N, int& r, int& I, int& J, string& output_dir, vector<string>& matrix_names){
    
    pt::ptree root;
    pt::read_json(filename, root);
    
    N = root.get<int>("n_nodes");
    r = root.get<int>("r");
    I = root.get<int>("initial_node");
    J = root.get<int>("final_node");
    string input_dir = root.get<string>("matrix_dir");
    output_dir = root.get<string>("result_dir");
    
    for (pt::ptree::value_type &name : root.get_child("matrix_names")){
        matrix_names.push_back(input_dir +  name.second.data());
    }
    
}
