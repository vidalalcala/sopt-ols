//
//  soptols.h
//
//
//  Created by Jose Alcala Burgos on 8/2/13.
//  Copyright [2013] Jose V. Alcala Burgos
//

#ifndef SRC_BASE_SOPTOLS_H_
#define SRC_BASE_SOPTOLS_H_

// Libraries
#include <armadillo>
#include <iostream>

// Project
#include "seqols.h"
#include "stochasticTools.h"

using namespace std;
using namespace arma;

/**
 * @brief Stochastic Optimization with Ordinary least squares
 * 
 */

class SOptOls {
 public:
    /**
    * Constructs the stochastic optimization problem.
    */
    SOptOls(const stochasticGradient& stoGrad, const mat& alphas_initial) {
        /**
        * Check that dimensions are consistent
        */
        _GLIBCXX_DEBUG_ASSERT(_par_dim == stoGRad.par_dim());

        /**
        * Set default optimization parameters
        */
        _par_dim = alphas_initial.n_cols;
        _n_predict_initial = alphas_initial.n_rows - 1;
        _alphas_initial = alphas_initial;
        _n_iterations  = 1000000;
        _detailed_output = 1;
        _outputfile = "output_soptols.txt";
        _gamma = 0.60;

        _stoGrad = stoGrad;
    }

    /**
     *Gets par_dim
     */
    int par_dim() const
    {return _par_dim;}

    /**
     *Gets n_predict_initial
     */
    int n_predict_initial() const
    {return _n_predict_initial;}

    /**
     *Gets n_iterations
     */
    int n_iterations() const
    {return _n_iterations;}

    /**
     * @brief Performs the stochastic optimization.
     */
    template<class _UniformRandomNumberGenerator>
    void optimize(_UniformRandomNumberGenerator& __urng) {
        mat X(_n_predict_initial + 1, _par_dim);
        X.rows(0, _n_predict_initial) = _alphas_initial;
        // The matrix of responses
        mat Y(_n_predict_initial, _par_dim);
        // The parameter alpha
        mat alpha(1, _par_dim);
        // The gradient with respect to the parameter alpha
        mat grad_alpha(1, _par_dim);

        // Generate the first n_predict_initial stochastic gradients.
        for (int i = 0 ; i < _n_predict_initial ; i++) {
            alpha = X.row(i);
            grad_alpha = _stoGrad(__urng, alpha);
            Y.row(i) = grad_alpha;
        }

        // Initialize the OLS estimator with n_predict_initial observations.
        SeqOls Estimator;
        Estimator.useObservations(X.rows(0, _n_predict_initial - 1),
                                  Y.rows(0, _n_predict_initial - 1));

        // Perform Robbins-Monro with Ordinary Least Squares
        mat H_i_estimator(_par_dim, _par_dim);
        alpha = X.row(_n_predict_initial);
        grad_alpha = _stoGrad(__urng, alpha);
        mat alpha_new(1, _par_dim);
        mat grad_alpha_new(1, _par_dim);

        for (int i = _n_predict_initial + 1 ; i < _n_iterations ; i++) {
            double i_double = static_cast<double>(i);
            H_i_estimator = (0.5) * (Estimator.G + Estimator.G.t());
            alpha_new = alpha - ((1.0 / pow(i_double, _gamma))
                                 * grad_alpha
                                 * (H_i_estimator));
            Estimator.addObservation(alpha, grad_alpha);
            grad_alpha_new = _stoGrad(__urng , alpha_new);
            alpha = alpha_new;
            grad_alpha = grad_alpha_new;
        }

        // Print the estimator
        alpha_new.print(" alpha_estimator : ");
        H_i_estimator.print(" H_inverse_estimator :");
        cout << " gamma : " << _gamma << endl;
        cout << " number of gradient samples : " << _n_iterations << endl;
    }

 private:
    int _par_dim; /*!< parameter dimension */
    int _n_predict_initial; /*!< The number of gradient samples used to
                            *initialize the stochastic optimization
                            */
    mat _alphas_initial;
    int _n_iterations; /*!< The number of stochastic optimization steps */
    double _gamma; /*!< The Robbins-Monro update has a factor
                   * @f$ 1/n^{\gamma} @f$
                   */
    bool _detailed_output;
    string _outputfile;
    stochasticGradient _stoGrad;
};

#endif  // SRC_BASE_SOPTOLS_H_
