
#include <iostream>
#include <string>
#include "system.hpp"
#include "observer.hpp"
#include <boost/numeric/odeint.hpp>
#include <fstream>
#include <sstream>

#define PI 3.14159265

using namespace std;
using namespace boost::numeric::odeint;


typedef std::vector<double> state_type;


std::vector<state_type> generate_particles(double x_1, double x_2, double y_1, double y_2, int x_cells,
                                           int y_cells, int particle_density) {
	std::vector<state_type> N;
	double step = (y_2 - y_1) / y_cells;
	for (int i = 0; i < x_cells; ++i) {
		for (int j = 0; j < y_cells; ++j) {
			for (int k = 1; k < particle_density + 1; ++k) {
				for (int l = 1; l < particle_density + 1; ++l) {
					state_type x { x_1 + step * i
							+ k * step / (particle_density + 1), y_1 + step * j
							+ l * step / (particle_density + 1) };
					N.push_back(x);
				}
			}
		}
	}
	return N;
}

struct matrix {
	std::vector<std::vector<double>> A;
	int dim;

	matrix(int n) {
		dim = n;
		A.resize(n);
		for (int i = 0; i < A.size(); ++i)
			A[i].resize(n);
	}

	double& operator()(int i, int j) {
		return A[i][j];
	}

	void smart_print(ofstream& file) {
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				if (A[i][j] != 0)
                    file << i << "\t" << j << "\t" << A[i][j] << "\n";
			}
		}
	}

	void normalize_out() {
		std::vector<double> out_strenghts(dim);
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++)
				out_strenghts[i] += A[i][j];
		}

		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++)
                if(A[i][j] != 0)
                    A[i][j] /= out_strenghts[i];
		}

	}

};

int evaluate_cell(double x, double y, double step, int x_cells) {
	int n_x = static_cast<int>(x / step);
	int n_y = static_cast<int>(y / step);
	return n_x + x_cells * n_y;
}


double x_1 = 0;
double x_2 = 2;
double y_1 = 0;
double y_2 = 1;
int x_cells = 50;
int y_cells = 25;
int particle_density = 10;
double step = (x_2 - x_1) / static_cast<double>(x_cells);
int N_nodes = x_cells*y_cells;

int main(int argc, char *argv[]) {
	std::string m_string = argv[1];
    std::string output_dir = argv[2];

	gyre_back system(0.1, 0.25, 0.2 * PI);
	double t0 = 0, tf = 15, dt = 0.05;
	
	int M = std::stoi(m_string);
	observer obs;
    
    
    for (int m = 0; m < M; ++m) {

        matrix A(N_nodes);
        std::vector<state_type> particles = generate_particles(x_1, x_2, y_1, y_2, x_cells, y_cells, particle_density);
        double t_start = t0 + m * (tf - t0) / M, t_end = t_start + (tf - t0) / M;
        
        for (int n = 0; n < particles.size(); ++n) {
                int init_cell = evaluate_cell(particles[n][0], particles[n][1], step, x_cells);
                state_type final_state = custom_integrate_adaptive<gyre_back>(
                        system, particles[n], t_start, t_end, dt, obs);
                if (n % 100000 == 0)
                    cout << n << endl;
                int final_cell = evaluate_cell(final_state[0], final_state[1], step, x_cells);
                A(init_cell, final_cell) += 1;
            }
            A.normalize_out();
            std::string filename = std::to_string(M) + "step_" + std::to_string(m) + ".dat";
            ofstream file(output_dir + filename);
            A.smart_print(file);
            file.close();
        }

}
