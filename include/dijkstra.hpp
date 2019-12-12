#ifndef DIJKSTRA_INCLUDE
#define DIJKSTRA_INCLUDE

#include <vector>
#include "containers.hpp"
#include "utils.hpp"

using namespace std;


double Dijkstra(Mat_vector& Mat, int m1, int m2, int i, int j, int M,
		std::vector<std::vector<int>>& U, std::vector<int>& Count,
		std::vector<int>& Path);


#endif
