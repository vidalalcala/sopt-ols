//
//  seqols.cpp
//
//
//  Created by Jose Vidal Alcala Burgos on 7/17/13.
//
//
//

//System includes
#include <iostream>
#include <cmath>

//Includes in the directory
#include "mtrand.h"
#include "seqols.h"
#include "seqolsTest.h"

#include "MonteCarloTools.h"

#include "/usr/include/armadillo"

using namespace std;
using namespace arma;


int main (int argc, char * const argv[])
{
    //Initialize the random number generator
	unsigned long init[4] = {time(0), 87563214, 875345, 874643}, length = 4;
	MTRand_int32 irand(init, length);
	MTRand_open drand;
    
    // Create synthetic data
    int p = 4 ;                         // # of parameters
    int n = 1000000 ;                     // # of samples
    mat X = randu<mat>(n,p) ;           // The matrix of predictors
    mat H = randu<mat>(p,p) ;           // The Hessian matrix for the quadratic loss
    H = 0.5 * ( H.t() + H ) ;           // Hessian is symmetric
    mat Sigma = randu<mat>(p,p) ;       // The covariance matrix for the quadratic loss
    Sigma = 0.5 * ( Sigma.t() + Sigma ) ;// Covariance is symmetric
    mat theta = randu<mat>(1,p) ;       // The parameter we will try to estimate
    mat Y(n,p) ;                        // The matrix of responses
    mat Z(n,p) ;                        // Matrix with standard normal entries
    
    // Create a n x p matrix with standard normal entries
    double z1,z2 ;
    for (int i = 0 ; i < n ; i++){
            for (int j = 0 ; j < p ; j++){
                normalSample( &z1 , &z2 , &drand) ;
                Z(i,j) = z1 ;
            }
    }
    
    //Generate synthetis responses
    Y = X * H - Z * Sigma * H ;
    for ( int i = 0 ; i < n ; i++){
        Y.row(i) = Y.row(i) + theta * H  ;
    }
    H.print("H: ") ;
    
    // Initialize the OLS estimator with p+1 observations.
    SeqOls Estimator ;
    Estimator.useObservations( X.rows(0,p) , Y .rows(0,p) ) ;
    Estimator.printEstimator() ;
    
    // Add the rest of the observations sequentially.
    for  ( int i = p + 1 ; i < n ; i++){
        Estimator.addObservation( X.row(i) , Y.row(i) ) ;
    }
    
    //Print the estimator
    Estimator.printEstimator() ;
    Estimator.testInverse();
}