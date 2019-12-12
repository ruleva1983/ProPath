#ifndef OBSERVER_INCLUDE
#define OBSERVER_INCLUDE

#include <vector>
#include <iostream>

using namespace std;

typedef std::vector<double> state_type;

struct observer {
	std::vector<state_type> states;
	std::vector<double> times;
	observer() {
		states = std::vector < state_type > (0);
		times = std::vector<double>(0);
	}

	void operator()(state_type x, double t) {
		states.push_back(x);
		times.push_back(t);
	}

	void print() {
		cout << "Observed trajectory: " << endl;
		for (int i = 0; i < states.size(); ++i)
			cout << " x = " << states[i][0] << "  y = " << states[i][1]
					<< "  t = " << times[i] << endl;
	}

};

#endif
