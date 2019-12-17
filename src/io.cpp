#include "io.hpp"


void write_Paths(std::vector<std::vector<int>>& Cammino,
		std::vector<double>& Probabilities, std::ofstream& output) {

	auto it_p = Probabilities.begin();
	for (auto it_c = Cammino.begin(); it_c < Cammino.end(); ++it_c) {
		for (int i = 0; i < (*it_c).size(); ++i) {
			output << (*it_c)[i] << " ";
		}
		output << *it_p << std::endl; // Adding other things to write
		++it_p;
	}

}
