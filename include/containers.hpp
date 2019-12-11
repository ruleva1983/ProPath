
#ifndef CONTAINERS_INCLUDE
#define CONTAINERS_INCLUDE


#include "Eigen/Dense"
#include "Eigen/Sparse"
#include <iostream>
#include <fstream>
#include <boost/concept_check.hpp>
#include <vector>
#include <string>


using namespace std;

class Mat_vector{
public:
    
    Mat_vector(int dimension, const std::vector<std::string>& s, std::string mode = "smart"): n_dimension(dimension){
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
  
  
    void smart_read(const std::vector<std::string>& s){  
        int m = 0;
        for (auto s_it = s.begin() ; s_it < s.end() ; ++s_it){
            int counter = 0;

            std::ifstream file_name(*s_it);
            std::cout << "Reading " << *s_it << "..." << std::endl;
            while ( !file_name.eof() )  // Check this bug
            {
    
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
  
    void standard_read(const std::vector<std::string>& s){  
        int m = 0;
        for (auto s_it = s.begin() ; s_it < s.end() ; ++s_it){
            int counter = 0;
            std::cout << "Reading " << *s_it << "..." << std::endl;
            int i = 0, j = 0;
            double value;
            std::ifstream file_name((*s_it));
            while ( !file_name.eof() ){  // Check this bug
                if (i == n_dimension){i = 0; ++j;}
                file_name >> value;
                if (value != 0){++counter;}
                M_sparse[m].insert(i,j) = value;
                ++i;
            }
        file_name.close();
        ++m;
        }
    }
 
    int size(){
        return M;
    }
  
    Eigen::SparseMatrix<double>& sparse(int m){
        return M_sparse[m];
    }
  
    std::vector<Eigen::SparseMatrix<double>> partial(int m1, int m2){
        return std::vector<Eigen::SparseMatrix<double>>(M_sparse.begin() + m1, M_sparse.begin() + m2);
    }
  
    std::vector<Eigen::SparseMatrix<double>> * pointer(int m){
        return &M_sparse + m;
    }
  
  
    int dimension() const {return n_dimension;}
    int steps() const {return M;}
 
private:
 
    std::vector<Eigen::SparseMatrix<double>> M_sparse;
    int M, n_dimension;
};


class Mat_access{
public:
    Mat_access(Mat_vector& Mat, int threshold = 0){
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
  
    Eigen::SparseMatrix<int>& sparse(int m){
        return M_sparse[m];
    }
    
    int dimension() const {return n_dimension;}
    int steps() const {return M;}
  
private:
    std::vector<Eigen::SparseMatrix<int>> M_sparse;
    int M, n_dimension;
};


class Mat_prod_access{
public:
    Mat_prod_access(Mat_access& Mat){
        int m = Mat.steps();
        Pairs = make_pairs(m);
        for(int i = 0; i < Pairs.size() ; ++i){
            M_Prod.push_back(make_product_sparse(Mat, Pairs[i].first,Pairs[i].second));
        }
    }
  
    int get_index(int i, int j){
        for (int k = 0; k < Pairs.size() ; ++k){
            if (Pairs[k].first == i && Pairs[k].second == j) {return k;}
        }
        std::cout << "No matrix found, returning no index";
        return -1;
    }
  
    Eigen::SparseMatrix<int>& m_prod(int m){
        return M_Prod[m];
    }
  
  
private:
    std::vector<std::pair<int,int>> make_pairs(int m){
        std::vector<std::pair<int,int>> P;
    
        for (int i = 0 ; i < m  ; ++i){
            for(int j = 1 ; j <= m - i ; ++j){
                P.push_back(std::pair<int,int>(j,j+i));
            }
        }
        return P;
    }
  
    Eigen::SparseMatrix<int> make_product_sparse(Mat_access& Mat, int i, int j){
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
  
private:
    std::vector<Eigen::SparseMatrix<int>> M_Prod;
    std::vector<std::pair<int,int>> Pairs;
};


#endif
