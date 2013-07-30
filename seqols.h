//
//  seqols.h
//  
//
//  Created by Jose Alcala Burgos on 7/18/13.
//
//

#ifndef ____seqols__
#define ____seqols__

#include <iostream>

#include "/usr/include/armadillo"

using namespace std;
using namespace arma;


// Sequential Ordinary Least Square class

class SeqOls{
public:
    void useObservations (mat , mat) ;
    void addObservation (mat , mat);
    void printEstimator();
    void testInverse() ;
    
private:
    int n ; // The number of observations
    int p ; // The number of paramters
    mat B ; // Estimator of B in y = x B
    mat P ; // Covariance matrix
    mat G ; // Inverse of the first p rows of B
};

#endif /* defined(____seqols__) */
