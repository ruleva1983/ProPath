
#ifndef CONTAINERS_INCLUDE
#define CONTAINERS_INCLUDE

#include "Eigen/Dense"
#include "Eigen/Sparse"
#include <iostream>
#include <fstream>
#include <boost/concept_check.hpp>
#include <vector>
#include <string>

//#include "utils.hpp"


using namespace std;

class Mat_vector{
public:
    
    Mat_vector(int dimension, const std::vector<std::string>& s, std::string mode = "smart");
  
    void smart_read(const std::vector<std::string>& s);
  
    void standard_read(const std::vector<std::string>& s);
 
    int size();
  
    Eigen::SparseMatrix<double>& sparse(int m);
  
    std::vector<Eigen::SparseMatrix<double>> partial(int m1, int m2);
  
    std::vector<Eigen::SparseMatrix<double>> * pointer(int m);
  
    int dimension() const; 
    
    int steps() const; 
 
private:
 
    std::vector<Eigen::SparseMatrix<double>> M_sparse;
    int M, n_dimension;
};


class Mat_access{
public:
    Mat_access(Mat_vector& Mat, int threshold = 0);
  
    Eigen::SparseMatrix<int>& sparse(int m);

    int dimension() const;
    int steps() const;
  
private:
    std::vector<Eigen::SparseMatrix<int>> M_sparse;
    int M, n_dimension;
};


class Mat_prod_access{
public:
    Mat_prod_access(Mat_access& Mat);
  
    int get_index(int i, int j);
  
    Eigen::SparseMatrix<int>& m_prod(int m);
  
private:
    std::vector<std::pair<int,int>> make_pairs(int m);
  
    Eigen::SparseMatrix<int> make_product_sparse(Mat_access& Mat, int i, int j);
  
private:
    std::vector<Eigen::SparseMatrix<int>> M_Prod;
    std::vector<std::pair<int,int>> Pairs;
};


#endif
