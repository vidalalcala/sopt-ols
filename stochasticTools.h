//
//  stochasticTools.h
//  
//
//  Created by Jose Alcala Burgos on 7/30/13.
//
//

#ifndef ____stochasticTools__
#define ____stochasticTools__

#include <iostream>
#include <random>

#include "/usr/include/armadillo"

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

class stochasticGradientQuadratic
{
    
public:
    /**
     * Constructs the gradient sampler with parameters
     * @f$ H,\Sigma, \alpha_{*} @f$ .
     */
    stochasticGradientQuadratic(const mat& __H , const mat& __Sigma , const mat& __alpha_optimal  ): _M_H(__H), _M_Sigma(__Sigma), _M_alpha_optimal(__alpha_optimal)
    {
        /**
         *Check that dimensions are consistent
         */
        par_dim = _M_alpha_optimal.n_cols ;
        _GLIBCXX_DEBUG_ASSERT( 1 == _M_alpha_optimal.n_rows);
        _GLIBCXX_DEBUG_ASSERT( _M_H.n_cols == _M_alpha_optimal.n_cols );
        _GLIBCXX_DEBUG_ASSERT( _M_H.n_rows == _M_alpha_optimal.n_cols );
        _GLIBCXX_DEBUG_ASSERT( _M_Sigma.n_cols == _M_alpha_optimal.n_cols );
        _GLIBCXX_DEBUG_ASSERT( _M_Sigma.n_rows == _M_alpha_optimal.n_cols );
    }
    
    /**
     *Gets H
     */
    mat H() const
    { return _M_H ; }
    
    /**
     *Gets Sigma
     */
    mat Sigma() const
    { return _M_Sigma ; }
    
    /**
     *Gets alpha_optimal
     */
    mat alpha_optimal() const
    { return _M_alpha_optimal ; }
    
    template<class _UniformRandomNumberGenerator>
    mat
    operator()(_UniformRandomNumberGenerator& __urng, const mat& __alpha ){
        // The standard normal sampler
        normal_distribution<double> normalSample(0.0,1.0);
        
        // Create a 1 x p matrix with standard normal entries
        mat Z(1, par_dim) ;
        for (int j = 0 ; j < par_dim ; j++){
            Z(0,j) = normalSample(__urng) ;
        }
        
        //the gradient sample
        mat estimator(1,par_dim) ;
        estimator = __alpha * _M_H - Z * _M_Sigma * _M_H ;
        estimator = estimator - _M_alpha_optimal * _M_H ;
        return estimator;
    }
    
private:
    mat _M_H ;
    mat _M_Sigma ;
    mat _M_alpha_optimal ;
    int par_dim ;
    
};

#endif /* defined(____stochasticTools__) */
