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


std::string index(int& I1, int& I2, int& J1, int& J2, int I, int J, int N) {
	std::string name = "";
	if (I == -1 && J == -1) // All pairs
			{
		I1 = 0;
		I2 = N;
		J1 = 0;
		J2 = N;
		name = "FromAll_ToAll_";
	} else if (I == -1)   // To J
			{

		I1 = 0;
		I2 = N;
		J1 = J;
		J2 = J + 1;
		name = "FromAll_To" + std::to_string(J) + "_";
	} else if (J == -1)   // From  I
			{
		I1 = I;
		I2 = I + 1;
		J1 = 0;
		J2 = N;

		name = "From" + std::to_string(I) + "_ToAll_";
	} else              // From I To J
	{
		I1 = I;
		I2 = I + 1;
		J1 = J;
		J2 = J + 1;
		name = "From" + std::to_string(I) + "_To" + std::to_string(J) + "_";
	}

	return name;
}
