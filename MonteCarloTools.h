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

void coefficientsGBM(   // Saves in array the volatility of a geometric brownian
                        // motion evaluated at (x[],t).
                     
    mat *drift ,        // GBM drift
    mat *volatility ,   // GBM volatility
    mat x ,             // GBM position
    double t );         // time


#endif
