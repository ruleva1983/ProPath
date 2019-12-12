#ifndef SYSTEM_INCLUDE
#define SYSTEM_INCLUDE

#include <cmath>
#include <vector>
#include <iostream>
#include <boost/numeric/odeint.hpp>

#include "observer.hpp"


#define PI 3.14159265

using namespace std;

typedef std::vector<double> state_type;


struct gyre {
    
    double m_A;
	double m_gamma;
	double m_omega;

	gyre(double A, double gamma, double omega) :
			m_A(A), m_gamma(gamma), m_omega(omega) {
	}

	void operator()(const state_type &x, state_type &dxdt, double t) const {
		double a = m_gamma * sin(m_omega * t);
		double b = 1 - 2 * m_gamma * sin(m_omega * t);
		double f = a * x[0] * x[0] + b * x[0];
		dxdt[0] = (-1) * PI * m_A * sin(PI * f) * cos(PI * x[1]);
		dxdt[1] = PI * m_A * cos(PI * f) * sin(PI * x[1]) * (2 * a * x[0] + b);
	}
};

struct gyre_back {
    
    double m_A;
	double m_gamma;
	double m_omega;

	gyre_back(double A, double gamma, double omega) :
			m_A(A), m_gamma(gamma), m_omega(omega) {
	}

	void operator()(const state_type &x, state_type &dxdt, double t) const {
		double a = m_gamma * sin(m_omega * (15 - t));
		double b = 1 - 2 * m_gamma * sin(m_omega * (15 - t));
		double f = a * x[0] * x[0] + b * x[0];
		dxdt[0] = PI * m_A * sin(PI * f) * cos(PI * x[1]);
		dxdt[1] = -PI * m_A * cos(PI * f) * sin(PI * x[1]) * (2 * a * x[0] + b);
	}
};




template<class System>
state_type custom_integrate_adaptive(const System& system, state_type &start_state,
                                     double start_time, double end_time, double dt,
                                     observer& obs) {
    controlled_runge_kutta < runge_kutta_dopri5<state_type> > stepper;

	const size_t max_attempts = 100;
	const char *error_string =
			"Integrate adaptive : Maximal number of iterations reached. A step size could not be found.";
	//size_t count = 0;

	//obs( start_state , start_time );
	while (start_time < end_time) {

		if ((start_time + dt) > end_time) {
			dt = end_time - start_time;
		}

		size_t trials = 0;
		controlled_step_result res = success;
		do {
			res = stepper.try_step(system, start_state, start_time, dt);
			++trials;
		} while ((res == fail) && (trials < max_attempts));
		if (trials == max_attempts)
			throw std::overflow_error(error_string);

		boundary_conditions(start_state);

		//++count;
	}

	//obs( start_state , start_time );
	return start_state;
}


#endif
