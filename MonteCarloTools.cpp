//
//  MonteCarloTools.cpp
//  AmericanGeometric
//
//  Created by Jose Alcala Burgos on 6/28/13.
//  Copyright (c) 2013 Jose V. Alcala. All rights reserved.
//


#include <math.h>
#include "mtrand.h"
#include "MonteCarloTools.h"
#include "/usr/include/armadillo"

using namespace arma;

//Standard normal cdf
double normcdf(double x)
{
	double b1 =  0.319381530;
	double b2 = -0.356563782;
	double b3 =  1.781477937;
	double b4 = -1.821255978;
	double b5 =  1.330274429;
	double p1  =  0.2316419;
	double c  =  0.39894228;
	
	if(x >= 0.0) {
		double t = 1.0 / ( 1.0 + p1 * x );
		return (1.0 - c * exp( -x * x / 2.0 ) * t *
				( t *( t * ( t * ( t * b5 + b4 ) + b3 ) + b2 ) + b1 ));
	}
	else {
		double t = 1.0 / ( 1.0 - p1 * x );
		return ( c * exp( -x * x / 2.0 ) * t *
				( t *( t * ( t * ( t * b5 + b4 ) + b3 ) + b2 ) + b1 ));
    }
}

//Standard normal samples generated with BoxMuller
void normalSample( double *z1, double *z2, MTRand_open *drand )
{
	//Box Muller
	double u1=(*drand)();
	double u2=(*drand)();
	double R=sqrt(-2*log(u1));  // the radial component
	double angle=2*M_PI*u2;		// the angle
	*z1=R*cos(angle);		// normal with standard deviation dt
	*z2=R*sin(angle);
}

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




