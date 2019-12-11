#ifndef UTILS_INCLUDE
#define UTILS_INCLUDE


#include "containers.hpp"
#include "Eigen/Dense"
#include "Eigen/Sparse"


Eigen::SparseMatrix<double> full_matrix(Mat_vector& Mat) {
    Eigen::SparseMatrix<double> P = Mat.sparse(0);
    for (int i = 1 ; i < Mat.steps() ; ++i)
        P = P * Mat.sparse(i);
    return P;
}


Eigen::SparseMatrix<int> to_access(const Eigen::SparseMatrix<double>& M,double threshold = 0.0){
    Eigen::SparseMatrix<int> A(M.rows(),M.cols());
    for (int i = 0; i < M.rows() ; ++i){
        for(int j = 0; j < M.cols() ; ++j){
            if (M.coeff(i,j) > threshold){A.insert(i,j) = 1;}
        }
    }
    return A;
}



#endif
