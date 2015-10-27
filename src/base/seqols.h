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

#include <armadillo>

using namespace std;
using namespace arma;

/**
 * Sequential Ordinary Least Square class
 */
class SeqOls{
public:
    /**
     * Perform linear regression with all the observations
     */
    void useObservations ( mat X /**
                                  * A n x p matrix with n predictors
                                  */
                          , mat Y /**
                                   * A n x p matrix with n responses,
                                   */
                          ) ;
    
    /**
     * Add one observation
     */
    void addObservation (mat x /**
                                * A 1 x p matrix with 1 predictors
                                */
                         
                         , mat y /**
                                  * A 1 x p matrix with 1 response
                                  */
                         ) ;
    
    
    void printEstimator() ;
    void testInverse() ;
    /**
     *  Inverse of the first p rows of B
     */
    mat G ;
    
private:
    /**
     *  The number of observations
     */
    int n ; 
    /**
     *  The number of paramters
     */
    int p ; 
    /**
     *  Estimator of B in y = x B
     */
    mat B ;
    /**
     *  Covariance matrix
     */
    mat P ;
    
};

#endif /* defined(____seqols__) */
