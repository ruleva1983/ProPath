#ifndef IO_INCLUDE
#define IO_INCLUDE

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;



void write_Paths(std::vector<std::vector<int>>& Cammino,
		std::vector<double>& Probabilities, std::ofstream& output);


std::string index(int& I1, int& I2, int& J1, int& J2, int I, int J, int N);

#endif
