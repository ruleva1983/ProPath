#ifndef UTILS_INCLUDE
#define UTILS_INCLUDE

#include "containers.hpp"
#include "Eigen/Sparse"
#include <chrono>


class Timer
{
public:
	Timer() : beg_(clock_::now()) {}
	void reset() { beg_ = clock_::now(); }
	double elapsed() const {
		return std::chrono::duration_cast<second_>
			(clock_::now() - beg_).count();
	}

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::ratio<1> > second_;
	std::chrono::time_point<clock_> beg_;
};


Eigen::SparseMatrix<double> full_matrix(Mat_vector& Mat);

Eigen::SparseMatrix<int> to_access(const Eigen::SparseMatrix<double>& , double);

#endif
