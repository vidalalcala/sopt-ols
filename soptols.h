//
//  soptols.h
//  
//
//  Created by Jose Alcala Burgos on 7/29/13.
//
//

#ifndef ____soptols__
#define ____soptols__

#include <iostream>

#include "/usr/include/armadillo"

using namespace std;
using namespace arma;

// Stochastic Optimization with ordinary least squares.

class SOptOls{
public:
    void iterate (mat , mat) ;
    void addObservation (mat , mat);
    void printEstimator();
    void testInverse() ;
    
private:
    
    int n ; // The number of observations
    int p ; // The number of parameters
    default_random_engine generator;
    
};

#endif /* defined(____seqols__) */
