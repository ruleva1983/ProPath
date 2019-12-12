#ifndef UTILS_INCLUDE
#define UTILS_INCLUDE

#include "containers.hpp"
#include "Eigen/Dense"
#include "Eigen/Sparse"


Eigen::SparseMatrix<double> full_matrix(Mat_vector& Mat);

Eigen::SparseMatrix<int> to_access(const Eigen::SparseMatrix<double>& M,double threshold = 0.0);

#endif
