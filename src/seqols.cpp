//
//  seqols.cpp
//
//
// Created by Jose V. Alcala Burgos on 7/30/13.
//  Copyright [2013] Jose V. Alcala Burgos
//
//

#include "base/seqols.h"

// System
#include <armadillo>

#include <iostream>
#include <cmath>

using namespace arma;
using namespace std;

void SeqOls::useObservations(mat X, mat Y  // A n x p matrix with n responses,
                                           // one response per row
                             ) {
    if (X.size() != Y.size()) {
        cout << " The predictor/response matrices should have the same size";
        cout << endl;
    }

    n = X.n_rows;
    p = X.n_cols;
    X = join_rows(X, ones(n, 1));
    P = inv((X.t()) * X);
    B = P * (X.t() * Y);
    G = inv(B.rows(0, p - 1));
}

void SeqOls::addObservation(mat x,
                            mat y
                            ) {
    if (x.size() != y.size()) {
        cout << " The predictor/response matrices should have the same size";
        cout << endl;
    }

    if (x.n_cols != p) {
        cout << " The new observation should have " << p << "columns" << endl;
    }

    if (x.n_rows != 1) {
        cout << " Add only ONE observation. " << endl;
    }

    n = n + 1;
    x = join_rows(x, ones(1, 1));
    double alpha;
    alpha = as_scalar((1.0 / (1.0 + x * P * x.t())));
    mat u = P * x.t();
    u = u.rows(0, p - 1);
    u = alpha * u;
    mat v = y - x * B;
    v = v.t();
    B = B + alpha * (P * x.t() * (y - x * B));
    P = P - alpha * (P * x.t() * x * P.t());
    double beta;
    beta = as_scalar(1.0 / (1.0 + v.t() * G * u));
    G = G - beta * (G * u * v.t() * G);
}

// Prints the Ols estimator
void SeqOls::printEstimator() {
    B.print(" B_estimator : ");
    G.print("G_estimator (Hessian inverse):");
}

// Tests that the inverse of the first p rows of B is equal to G.
void SeqOls::testInverse() {
    double tolerance = 0.00000001;
    mat error = (B.rows(0, p - 1) * G - eye<mat>(p, p));
    if (norm(error, 2) < tolerance) {
        cout << "The inverse of the estimator is correct." << endl;
    } else {
        cout << "The inverse of the estimator is incorrect." << endl;
    }
}
