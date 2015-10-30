//
//  stochasticTools.cpp
//
//
//  Created by Jose V. Alcala Burgos on 7/30/13.
//  Copyright [2013] Jose V. Alcala Burgos
//

#include "base/stochasticTools.h"

// System
#include <armadillo>

#include <iostream>
#include <random>

stochasticGradient::stochasticGradient(
    const mat& __H,
    const mat& __Sigma,
    const mat& __alpha_optimal): _M_H(__H),
                                 _M_Sigma(__Sigma),
                                 _M_alpha_optimal(__alpha_optimal) {
        /**
         *Check that dimensions are consistent
         */
        _M_par_dim = _M_alpha_optimal.n_cols;
        _GLIBCXX_DEBUG_ASSERT(1 == _M_alpha_optimal.n_rows);
        _GLIBCXX_DEBUG_ASSERT(_M_H.n_cols == _M_alpha_optimal.n_cols);
        _GLIBCXX_DEBUG_ASSERT(_M_H.n_rows == _M_alpha_optimal.n_cols);
        _GLIBCXX_DEBUG_ASSERT(_M_Sigma.n_cols == _M_alpha_optimal.n_cols);
        _GLIBCXX_DEBUG_ASSERT(_M_Sigma.n_rows == _M_alpha_optimal.n_cols);
    }
