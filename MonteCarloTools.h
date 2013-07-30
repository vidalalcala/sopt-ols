//
//  MonteCarloTools.h
//  AmericanGeometric
//
//  Created by Jose Alcala Burgos on 6/28/13.
//  Copyright (c) 2013 Jose V. Alcala. All rights reserved.
//

#ifndef AmericanGeometric_MonteCarloTools_h
#define AmericanGeometric_MonteCarloTools_h

//include types
#include "/usr/include/armadillo"
using namespace arma;


double normcdf(     //Standard normal cdf
    
               
    double x);      // The fnction result is P( Z < x )

//-----------------------

void normalSample( // Generates two standard normals using the Box-Muller algorithm.
    
                  
    double *z1,             //Pointer to first normal
    double *z2,             //Pointer to second normal
    MTRand_open *drand );   //Pointer to a random number generator 

//-----------------------

void coefficientsGBM(   // Saves in array the volatility of a geometric brownian
                        // motion evaluated at (x[],t).
                     
    mat *drift ,        // GBM drift
    mat *volatility ,   // GBM volatility
    mat x ,             // GBM position
    double t );         // time



#endif
