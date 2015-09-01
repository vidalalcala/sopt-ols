//
//  MonteCarloTools.cpp
//  AmericanGeometric
//
//  Created by Jose Alcala Burgos on 6/28/13.
//  Copyright (c) 2013 Jose V. Alcala. All rights reserved.
//

//include C++11 random
#include <random>
#include <math.h>
#include "MonteCarloTools.h"
#include <armadillo>

using namespace arma;

/*
void coefficientsGBM( mat *drift , mat *volatility , mat x , double t)
{   //Check that dimensions are correct
    int BM_dim ;
    BM_dim = mu.n_rows ;
    
    if ( sigma.n_rows != BM_dim || sigma.n_cols != BM_dim ){
        throw invalid_argument("The dimensions of sigma and mu do not agree.");
    }
    
	//Check if the sigma matrix is invertible
    if ( fabs(det(sigma)) < 0.000000000000001){
        cout << "sigma is not invertible, det_sigma = " << fabs(det(sigma))<< endl;
    }
    
    //Calculate the volatility
    for (int i = 0 ; i < BM_dim; i++) {
		for (int j=0; j < BM_dim; j++) {
			(*volatility)(i,j) = x(i,0)*sigma(i,j) ;
		}
	}
    
    //Calculate the drift
    for (int i = 0 ; i < BM_dim; i++) {
		(*drift)(i,0) = mu(i,0) ;
		for (int l=0; l < BM_dim; l++) {
			(*drift)(i,0) = (*drift)(i,0) + (0.5)*sigma(i,l)*sigma(i,l) ;
		}
		(*drift)(i,0) = x(i,0)*((*drift)(i,0));
	}
    
    
}*/




