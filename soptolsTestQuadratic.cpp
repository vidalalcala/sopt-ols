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
    
    // The Robbins Monro iteration has a 1/n^{\gamma} factor in the update.
    double gamma = 0.60 ;
    
    // # of iterations in the stochastic optimization
    int n_iter = par_dim + 100000 ;
    
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
    stochasticGradientQuadratic stoGrad  ( H , Sigma , alpha_optimal);
    
    // Create the first n +1  samples randomly
    // The matrix with n+1 initial predictors
    mat X = randu<mat>( n + 1 , par_dim ) ;
    // The matrix of responses
    mat Y(n,par_dim) ;
    // The parameter alpha
    mat alpha(1,par_dim);
    // The gradient with respect to the parameter alpha
    mat grad_alpha(1,par_dim) ;                   
    
    //Generate the first n predictors randomly
    for (int i = 0 ; i < n ; i++){
        alpha = X.row(i) ;
        grad_alpha = stoGrad( generator , alpha ) ;
        Y.row(i) = grad_alpha ;
    }
    
    // Initialize the OLS estimator with n observations.
    SeqOls Estimator ;
    Estimator.useObservations( X.rows(0, n - 1 ) , Y .rows(0, n - 1 ) ) ;
    
    //Perform RobbinsMonro with Ordinary Least Squares
    mat H_i_estimator(par_dim,par_dim) ;
    alpha = X.row( n ) ;
    grad_alpha = stoGrad( generator , alpha ) ;
    mat alpha_new(1,par_dim) ;
    mat grad_alpha_new(1,par_dim) ;
    
    for  ( int i = n + 1 ; i < n_iter ; i++){
        double i_double = (double) i ;
        //cout << i_double << endl ;
        H_i_estimator = (0.5)*(Estimator.G + Estimator.G.t()) ;
        alpha_new = alpha - (1.0/pow(i_double,gamma))*grad_alpha*(H_i_estimator);
        Estimator.addObservation( alpha , grad_alpha ) ;
        grad_alpha_new = stoGrad( generator , alpha_new );
        alpha = alpha_new ;
        grad_alpha = grad_alpha_new ;
    }
    
    //Print the estimator
    alpha_new.print(" alpha_estimator : ") ;
    H_i_estimator.print(" H_inverse_estimator :") ;
    cout << " gamma : " << gamma << endl ;
    cout << " number of gradient samples : " << n_iter << endl ;
    return 0 ;
}