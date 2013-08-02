//
//  soptolsTestQuadratic.cpp
//  
//
//  Created by Jose Alcala Burgos on 7/30/13.
//
//

#include "soptolsTestQuadratic.h"

//System includes
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>

//Includes in the directory
#include "seqols.h"
#include "stochasticTools.h"
#include "soptols.h"

#include "/usr/include/armadillo"

using namespace std;
using namespace arma;


int main (int argc, char * const argv[])
{
	
    //Initialize the random number generator
    mt19937 generator;
    
    // Simulation parameters
    
    // # of parameters
    int par_dim = 4 ;
    
    // # of samples used to initialize the ols estimator.
    // We use par_dim + 1 samples to ensure full rank in the linear regression.
    int n = par_dim + 1 ;
    
    //Inititalize the quadratic test parameters randomly.
    // The Hessian matrix for the quadratic loss.
    mat H = randu<mat>(par_dim,par_dim) ;
    
    // Hessian is symmetric.
    H = 0.5 * ( H.t() + H ) ;
    
    // The covariance matrix for the quadratic loss.
    mat Sigma = randu<mat>( par_dim , par_dim ) ;
    
    // Covariance is symmetric.
    Sigma = 0.5 * ( Sigma.t() + Sigma ) ;
    
    // The parameter we will try to estimate.
    mat alpha_optimal = randu<mat>(1,par_dim) ;
    
    // Print to screen the parameters created randomly.
    H.print(" H : ");
    mat G = H.i() ;
    G.print(" G : ") ;
    Sigma.print(" Sigma : ");
    alpha_optimal.print(" alpha_optimal : ");
    
    //Construct the stochastic gradient sampler
    stochasticGradient stoGrad  ( H , Sigma , alpha_optimal);
    
    // Create the first n +1  samples randomly
    // The matrix with n+1 initial predictors
    mat X = randu<mat>( n + 1 , par_dim ) ;
    
    // Construct the Stochastic Optimziation
    SOptOls sopt (stoGrad, X ) ;
    sopt.optimize(generator) ;
    
    return 0 ;
}