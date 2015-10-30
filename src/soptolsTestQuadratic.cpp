//
//  soptolsTestQuadratic.cpp
//
//
//  Created by Jose V. Alcala Burgos on 7/30/13.
//  Copyright [2013] Jose V. Alcala Burgos
//

#include "base/soptolsTestQuadratic.h"

// System
#include <armadillo>

#include <cmath>
#include <ctime>
#include <iostream>
#include <random>

// Project
#include "base/seqols.h"
#include "base/soptols.h"
#include "base/stochasticTools.h"

using arma::mat;


int main(int argc, char * const argv[]) {
  // Initialize the random number generator
  mt19937 generator;

  // Simulation parameters
  int num_parameters = 4;
  int num_initial_samples = num_parameters + 1;  // Ensure precision full rank

  // Inititalize the quadratic test parameters randomly.

  // The Hessian matrix for the quadratic loss.
  mat H = randu<mat>(num_parameters, num_parameters);
  H = 0.5 * (H.t() + H);  // Hessian is symmetric

  // The covariance matrix for the quadratic loss.
  mat Sigma = randu<mat>(num_parameters, num_parameters);
  Sigma = 0.5 * (Sigma.t() + Sigma);

  // The parameter we will try to estimate.
  mat alpha_optimal = randu<mat>(1, num_parameters);

  // Print to screen the parameters created randomly.
  H.print(" H : ");
  mat G = H.i();
  G.print(" G : ");
  Sigma.print(" Sigma : ");
  alpha_optimal.print(" alpha_optimal : ");

  // Construct the stochastic gradient sampler
  stochasticGradient stoGrad(H, Sigma, alpha_optimal);

  // Create the first num_initial_samples +1  samples randomly
  // The matrix with num_initial_samples+1 initial predictors
  mat X = randu<mat>(num_initial_samples + 1, num_parameters);

  // Construct the Stochastic Optimization
  SOptOls sopt(stoGrad, X);
  sopt.optimize(generator);

  return 0;
}
