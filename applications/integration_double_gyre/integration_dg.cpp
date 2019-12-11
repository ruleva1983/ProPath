
#include <iostream>
#include <string>
#include "system.hpp"

#define PI 3.14159265

using namespace std;

typedef std::vector<double> state_type;

void boundary_conditions(state_type& x) {
	if (x[0] > 2.0)
		x[0] = 2.0;

	if (x[0] < 0.0)
		x[0] = 0.0;

	if (x[1] > 1.0)
		x[1] = 1.0;

	if (x[1] < 0.0)
		x[1] = 0.0;
}



int main(int argc, char *argv[]) {
	ostringstream ofs;
	boost::archive::text_oarchive ar(ofs);
	std::string m_string = argv[1];

	gyre_back system(0.1, 0.25, 0.2 * PI);
	double t0 = 0, tf = 15, dt = 0.05;
	std::string output_dir = "./";
	int M = std::stoi(m_string);
	observer obs;

	for (int m = 0; m < M; ++m) {

		matrix A;
		std::vector<state_type> particles = generate_particles();
		double t_start = t0 + m * (tf - t0) / M, t_end = t_start
				+ (tf - t0) / M;

		for (int n = 0; n < particles.size(); ++n) {
			int init_cell = evaluate_cell(particles[n][0], particles[n][1]);
			state_type final_state = custom_integrate_adaptive<gyre_back>(
					system, particles[n], t_start, t_end, dt, obs);
			if (n % 100000 == 0)
				cout << n << endl;
			int final_cell = evaluate_cell(final_state[0], final_state[1]);
			A(init_cell, final_cell) += 1;
		}
		A.normalize_out();
		std::string filename = std::to_string(M) + "step_" + std::to_string(m)
				+ ".dat";
		ofstream file(output_dir + filename);
		A.smart_print(file);
		file.close();
	}

}
