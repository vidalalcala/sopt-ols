//
//  stochasticTools.h
//
//
//  Created by Jose V. Alcala Burgos on 7/30/13.
//  Copyright [2013] Jose V. Alcala Burgos
//

#ifndef SRC_BASE_STOCHASTICTOOLS_H_
#define SRC_BASE_STOCHASTICTOOLS_H_

// System
#include <armadillo>

#include <iostream>
#include <random>

using namespace std;
using namespace arma;

/**
 * @brief Gradient sampler for the quadratic loss in LeCun , Schaul, Zhang (2013).
 *
 * Gradient sampler for the loss function
 * @f[
 * L = 0.5 x H x^T
 * @f]
 *
 * where @f$ x = \alpha - (\alpha_{*} + \Sigma Z) @f$ and @f$ Z @f$ is a standard
 * normal random variable. Vectors like @f$ \alpha,Z @f$ are row vectors
 * and the matrices @f$ H,\Sigma @f$ are square matrices.The default parameters
 * @f$ H,\Sigma,\alpha_{*} @f$ are two identity matrices and the zero vector.
 */

class stochasticGradient
{
    
public:
    stochasticGradient(){}
    /**
     * Constructs the gradient sampler with parameters
     * @f$ H,\Sigma, \alpha_{*} @f$ .
     */
     
    stochasticGradient(
        const mat& __H, 
        const mat& __Sigma, 
        const mat& __alpha_optimal);
    
    /**
     *Gets H
     */
    mat H() const
    {return _M_H;}
    
    /**
     *Gets Sigma
     */
    mat Sigma() const
    {return _M_Sigma;}
    
    /**
     * Gets par_dim
     */
    
    int par_dim() const
    {return _M_par_dim;}
    
    /**
     *Gets alpha_optimal
     */
    mat alpha_optimal() const
    {return _M_alpha_optimal;}
    
    template<class _UniformRandomNumberGenerator>
    mat
    operator()(_UniformRandomNumberGenerator& __urng, const mat& __alpha){
        // The standard normal sampler
        normal_distribution<double> normalSample(0.0,1.0);
        
        // Create a 1 x p matrix with standard normal entries
        mat Z(1, _M_par_dim) ;
        for (int j = 0 ; j < _M_par_dim ; j++){
            Z(0,j) = normalSample(__urng);
        }
        
        //the gradient sample
        mat estimator(1, _M_par_dim);
        estimator = __alpha * _M_H - Z * _M_Sigma * _M_H;
        estimator = estimator - _M_alpha_optimal * _M_H;
        return estimator;
    }
    
private:
    mat _M_H;
    mat _M_Sigma;
    mat _M_alpha_optimal;
    int _M_par_dim;
    
};

#endif  // SRC_BASE_STOCHASTICTOOLS_H_
