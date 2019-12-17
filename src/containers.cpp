#include "Eigen/Dense"
#include "Eigen/Sparse"
#include <iostream>
#include <fstream>
#include <boost/concept_check.hpp>
#include <vector>
#include <string>
#include "utils.hpp"
#include "containers.hpp"

using namespace std;


Mat_vector::Mat_vector(int dimension, const std::vector<std::string>& s, std::string mode = "smart"): n_dimension(dimension){
    M = s.size();
    M_sparse.resize(M);
    for(auto it = M_sparse.begin() ; it < M_sparse.end() ; ++it){
        (*it).resize(n_dimension, n_dimension);
    }
      
    if(mode == "smart")
        smart_read(s);
      
    else if(mode == "standard")
        standard_read(s);
      
    else
        std::cout << "Wrong inizialization mode for Mat_vector";
}
  
void Mat_vector::smart_read(const std::vector<std::string>& s){  
    int m = 0;
    for (auto s_it = s.begin() ; s_it < s.end() ; ++s_it){
        int counter = 0;

        std::ifstream file_name(*s_it);
        std::cout << "Reading " << *s_it << "..." << std::endl;
        while ( !file_name.eof() ){
    
            int i, j;
            double value;
            ++counter;
    
            file_name >> i >> j >> value;
    
            if ( file_name.eof() )
                break;
    
            if (value > 0.00001)
                M_sparse[m].insert(i,j) = value;
        }
        file_name.close();
        ++m;
    }
}
  
void Mat_vector::standard_read(const std::vector<std::string>& s){  
    int m = 0;
    for (auto s_it = s.begin() ; s_it < s.end() ; ++s_it){
        int counter = 0;
        std::cout << "Reading " << *s_it << "..." << std::endl;
        int i = 0, j = 0;
        double value;
        std::ifstream file_name((*s_it));
        while ( true ){
            if (i == n_dimension){i = 0; ++j;}
            file_name >> value;
            if (value != 0){++counter;}
            M_sparse[m].insert(i,j) = value;
            ++i;
            if (j == n_dimension - 1){if (i == n_dimension) break;}
        }
    file_name.close();
    ++m;
    }
}
 
int Mat_vector::size(){
    return M;
}
  
Eigen::SparseMatrix<double>& Mat_vector::sparse(int m){
    return M_sparse[m];
}
  
std::vector<Eigen::SparseMatrix<double>> Mat_vector::partial(int m1, int m2){
    //Assert that these numbers are within range
    return std::vector<Eigen::SparseMatrix<double>>(M_sparse.begin() + m1, M_sparse.begin() + m2);
}
  
std::vector<Eigen::SparseMatrix<double>> * Mat_vector::pointer(int m){
    return &M_sparse + m;
}
  
int Mat_vector::dimension() const {return n_dimension;}

//TODO This function can be eliminated, equivalent to size()
int Mat_vector::steps() const {return M;}



Mat_access::Mat_access(Mat_vector& Mat, int threshold){
    n_dimension = Mat.dimension();
    M = Mat.size();
    
    M_sparse.resize(M);
    
    for(auto it = M_sparse.begin() ; it < M_sparse.end() ; ++it){
        (*it).resize(n_dimension, n_dimension);
    }
    
    for (int m = 0 ; m < M ; ++m){
        M_sparse[m] = to_access(Mat.sparse(m),threshold);
    }
}

Eigen::SparseMatrix<int>& Mat_access::sparse(int m){
        return M_sparse[m];
}
    
int Mat_access::dimension() const {return n_dimension;}
int Mat_access::steps() const {return M;}




Mat_prod_access::Mat_prod_access(Mat_access& Mat){
    int m = Mat.steps();
    Pairs = make_pairs(m);
    for(int i = 0; i < Pairs.size() ; ++i){
        M_Prod.push_back(make_product_sparse(Mat, Pairs[i].first,Pairs[i].second));
    }
}
  
int Mat_prod_access::get_index(int i, int j){
    for (int k = 0; k < Pairs.size() ; ++k){
        if (Pairs[k].first == i && Pairs[k].second == j) {return k;}
    }
    std::cout << "No matrix found, returning no index";
    return -1;
}
  
Eigen::SparseMatrix<int>& Mat_prod_access::m_prod(int m){
    return M_Prod[m];
}
  

std::vector<std::pair<int,int>> Mat_prod_access::make_pairs(int m){
    std::vector<std::pair<int,int>> P;
    
    for (int i = 0 ; i < m  ; ++i){
        for(int j = 1 ; j <= m - i ; ++j){
            P.push_back(std::pair<int,int>(j,j+i));
        }
    }
    return P;
}
  
Eigen::SparseMatrix<int> Mat_prod_access::make_product_sparse(Mat_access& Mat, int i, int j){
    if (i == j){
        return Mat.sparse(i-1);
    }
    else {
        int counter;
        for (int k = 0; k < Pairs.size(); ++k){
            if (Pairs[k].first == i+1 && Pairs[k].second == j){
                counter = k;
                break;
            }
        }
        return Mat.sparse(i-1)*M_Prod[counter];
    }
}


