#ifndef UTILS_INCLUDE
#define UTILS_INCLUDE

#include "containers.hpp"
#include "Eigen/Sparse"


Eigen::SparseMatrix<double> full_matrix(Mat_vector& Mat);

Eigen::SparseMatrix<int> to_access(const Eigen::SparseMatrix<double>& , double);

#endif
