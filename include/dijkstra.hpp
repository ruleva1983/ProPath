#ifndef DIJKSTRA_INCLUDE
#define DIJKSTRA_INCLUDE

#include <vector>
#include "containers.hpp"
#include "utils.hpp"

using namespace std;


double Dijkstra(Mat_vector&, int, int, int, int, int,
        std::vector<std::vector<int>>& U, std::vector<int>&,
        std::vector<int>&);



void useful_points(Mat_prod_access&, int, int, int, int,
        std::vector<int>&, std::vector<std::vector<int>>&);

#endif
