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


class RandomFunction
{
public:
    
    // constructors and reset functions
    explicit RandomFunction(mat theta);
    explicit RandomFunction(const mat& theta);
    void reset();
    
    // generating functions
    template<class URNG>
    mat operator()(URNG& g);
    template<class URNG>
    mat operator()(URNG& g, const math& theta);
    
    // property functions
    mat param() const;
    void param(const mat& theta);
};

#endif /* defined(____stochasticTools__) */
