#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

#include "containers.hpp"
#include "dijkstra.hpp"
#include "utils.hpp"
#include "io.hpp"

#include "json_reader.hpp"


using namespace std;


int main(int argc, char *argv[]) {
    
    std::string config = argv[1];
    
    string output_dir;
    vector<string> matrix_names;
    int N, r, I, J;
    parse_json(config, N, r, I, J, output_dir, matrix_names);
    int M = matrix_names.size();
    
    double eps = 0.1;
    
    Timer t;
    Mat_vector Mat(N, matrix_names, "smart");
    std::cout << "Time to read matrices from file: " << t.elapsed() << " sec "
            << std::endl;
    
	t.reset();
	Mat_access Mat_access(Mat, 0.0);
    std::cout << "Time to build single step accessibility matrices: "
            << t.elapsed() << " sec " << std::endl;

	t.reset();
	Mat_prod_access Mat_prod(Mat_access);
	std::cout << "Time to make matrix products: " << t.elapsed() << " sec "
            << std::endl;

	t.reset();
	Eigen::SparseMatrix<double> Full_mat = full_matrix(Mat);
	std::cout << "Time to make full matrix product: " << t.elapsed() << " sec "
			<< std::endl;

	t.reset();
	// Selecting indexes
    
    int I1, I2, J1, J2;
    string output_file = index(I1, I2, J1, J2, I, J, N);
    cout << "Opening output file " + output_file + "...\n";
	std::ofstream Pathpro(output_dir + output_file + "M=" +std::to_string(M) + "_r=" + std::to_string(r) + ".dat");
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

				// Writing into file stream Pathpro
				if (r == 0) {
					int index = Mat_prod.get_index(1, M);
					for (int m = 0; m <= M; ++m)
                        Pathpro << PathMAX[m] << " ";
                    Pathpro << ProMAX << " " << Full_mat.coeff(I, J) << " "
                            << Mat_prod.m_prod(index).coeff(I, J) << " "
							<< ProMAX / Full_mat.coeff(I, J) << endl;
				}

            }
        }
}

    Pathpro.close();
    std::cout << "Time for Dijkstra: " << t.elapsed() << " sec " << std::endl;
    
}

