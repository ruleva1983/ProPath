#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

#include "containers.hpp"
#include "dijkstra.hpp"
#include "utils.hpp"
#include "io.hpp"

using namespace std;


int main(int argc, char *argv[]) {
    
    std::string N_string = argv[1];
    std::string m_string = argv[2];
    std::string input_dir = argv[3];
    std::string output_dir = argv[4];
    
	// Reading parameters 
    int N = std::stoi(N_string);
	int M = std::stoi(m_string);
    int r = 0, I = -1, J = -1;
	double eps = 0.1;

	// Reading matrices

	string s_init = input_dir;
	string s_fin = ".dat";
	vector < string > files;

	for (int i = 0 ; i < M ; i++){
	 string s_n = std::to_string(i);
	 files.push_back(s_init + m_string + "step_" + s_n + s_fin);
    }

    
	//Timer t;
	Mat_vector Mat(N, files, "smart");
	//std::cout << "Time to read matrices from file: " << t.elapsed() << " sec "
	//		<< std::endl;
    
	//t.reset();
	Mat_access Mat_access(Mat, 0.0);
	//std::cout << "Time to build single step accessibility matrices: "
	//		<< t.elapsed() << " sec " << std::endl;

	//t.reset();
	Mat_prod_access Mat_prod(Mat_access);
	//std::cout << "Time to make matrix products: " << t.elapsed() << " sec "
	//		<< std::endl;

	//t.reset();
	Eigen::SparseMatrix<double> Full_mat = full_matrix(Mat);
	//std::cout << "Time to make full matrix product: " << t.elapsed() << " sec "
	//		<< std::endl;

	//t.reset();
	// Selecting indexes
/*
	int I1, I2, J1, J2;
	string output_file = index(I1, I2, J1, J2, I, J, N);
	cout << "Opening output file " + output_file + "...\n";
	std::ofstream Pathpro(
			output_dir + output_file + "M=" + std::to_string(M) + "_r="
					+ std::to_string(r) + "_back" + s_fin);
	//std::ofstream Pathpro(output_dir + output_file + "M=" +std::to_string(M) + "_r=" + std::to_string(r) + s_fin);
	// Main Loop

	cout << "Main loop Starting" << endl;

	for (I = I1; I < I2; ++I) {
		if (I % 100 == 0) {
			cout << "Starting loop for point " << I << "." << endl;
		}
		for (J = J1; J < J2; ++J) {
			int index = Mat_prod.get_index(1, M);
			if (Mat_prod.m_prod(index).coeff(I, J) > 0) {
				// Selecting useful points
				std::vector<int> Count(M - 1);
				std::vector<std::vector<int>> U;
				useful_points(Mat_prod, M, N, I, J, Count, U);

				///// Initial Djkstra Algorithm Calling /////
				std::vector<int> PathMAX;
				double ProMAX = Dijkstra(Mat, 0, M, I, J, M, U, Count, PathMAX);
				//double ProMax = new_Dijkstra(Mat.pointer(0), M, I, J, &U, &Count, PathMAX);

				// Writing into file stream Pathpro
/*				if (r == 0) {
					int index = Mat_prod.get_index(1, M);
					//for (int m = 0; m <= M; ++m)
				//		Pathpro << PathMAX[m] << " ";
					//Pathpro << ProMAX << " " << Full_mat.coeff(I, J) << " "
					//		<< Mat_prod.m_prod(index).coeff(I, J) << " "
					//		<< ProMAX / Full_mat.coeff(I, J) << endl;
				}

				if (r == 1) {
					int Num_path = 0;
					std::vector<std::vector<int>> Cammino;
					std::vector<std::vector<double>> Prob;
					for (int m = 1; m <= M - 1; ++m) {
						for (int k = 0; k < Count[m - 1]; ++k) {
							std::vector<int> Path1, Path2;
							double ProAUX = Dijkstra(Mat, 0, m, I, U[m - 1][k],
									M, U, Count, Path1)
									* Dijkstra(Mat, m, M, U[m - 1][k], J, M, U,
											Count, Path2);
							if (ProAUX > eps * ProMAX) {
								Prob.push_back(std::vector<double> { ProAUX,
										static_cast<double>(Num_path) });
								Path1.insert(Path1.end(), Path2.begin() + 1,
										Path2.end());
								Cammino.push_back(Path1);
								Num_path++;
							}
						}
					}

//					std::vector<double> Probabilities = Path_sort(Cammino, Prob);
//					write_Paths(Cammino, Probabilities, Pathpro);

				}

			}
		}
}

//	Pathpro.close();
	//std::cout << "Time for Dijkstra: " << t.elapsed() << " sec " << std::endl;
*/    
}

