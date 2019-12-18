#include <vector>
#include "containers.hpp"
#include "utils.hpp"


using namespace std;


void useful_points(Mat_prod_access& Mat_prod, int M, int N, int I, int J,
		std::vector<int>& Count, std::vector<std::vector<int>>& U) {
	for (int m = 1; m < M; ++m) {
		U.push_back(std::vector<int>(0));
		int index1 = Mat_prod.get_index(1, m);
		int index2 = Mat_prod.get_index(m + 1, M);
		for (int a = 0; a < N; ++a) {
			if (Mat_prod.m_prod(index1).coeff(I, a) != 0
					&& Mat_prod.m_prod(index2).coeff(a, J) != 0) {
				U[m - 1].push_back(a);
				Count[m - 1]++;
			}
		}
	}

}

double Dijkstra(Mat_vector& Mat, int m1, int m2, int i, int j, int M,
		std::vector<std::vector<int>>& U, std::vector<int>& Count,
		std::vector<int>& Path) {
    /**
    Dijkstra shortest path algorithm applied to for a temporal weighted network.

    This function finds the shortest/most probable path in a temporal weighted network described
    by a set of weighted adjacency matrices. It returns the probability of the associated most
    probable path
    

    @param  Mat. Vector of matrices..
    @param  m1. Integer 
    @return Description of the return value
    */
	
    
    // Check m2 > m1
	// If there is only one step
	if (m2 == m1 + 1) {
		Path = std::vector<int> { i, j };
		return Mat.sparse(m1).coeff(i, j);
	} else {

		std::vector<std::vector<double>> Fun(M - 1);
		for (int m = 0; m < U.size(); ++m) {
			Fun[m].resize(U[m].size());
		}

		for (int k = 0; k < Count[m1]; ++k) {
			Fun[m1][k] = Mat.sparse(m1).coeff(i, U[m1][k]);
		}

		if (m2 == m1 + 2) {
			double Aux, Proo = 0;
			for (int k = 0; k < Count[m1]; ++k) {
				Aux = Fun[m1][k] * Mat.sparse(m1 + 1).coeff(U[m1][k], j);
				if (Aux > Proo) {
					Proo = Aux;
					Path = std::vector<int> { i, U[m1][k], j };
				}
			}
			return Proo;
		} else {
			double Aux, Proo = 0;
			int node;
			Path.push_back(i);
			for (int m = m1 + 1; m <= m2 - 2; ++m){ // Number of double for loops to do
                for (int l = 0; l < Count[m]; ++l) {
					for (int k = 0; k < Count[m - 1]; ++k) {
						Aux = Fun[m - 1][k]
								* Mat.sparse(m).coeff(U[m - 1][k], U[m][l]);
						if (Aux > Fun[m][l]) {
							Fun[m][l] = Aux;
							node = U[m][l];
						}
					}
				}
				Path.push_back(node);
			}

			// Last step
			for (int k = 0; k < Count[m2 - 2]; ++k) {

				Aux = Fun[m2 - 2][k]
						* Mat.sparse(m2 - 1).coeff(U[m2 - 2][k], j);
				if (Aux > Proo) {
					Proo = Aux;
					node = U[m2 - 2][k];
				}
			}
			Path.push_back(node);
			Path.push_back(j);
			return Proo;
		}

	}

}




