sopt-ols
========

[![Build Status](https://travis-ci.org/vidalalcala/sopt-ols.svg?branch=master)](https://travis-ci.org/vidalalcala/sopt-ols)

Stochastic optimization using ordinary least squares to approximate the inverse Hessian. 
The code tests a variant of the sequential ordinary least squares estimator proposed by 
Robbins and modified by Alcala & Goodman with a noise quadratic loss function described
by LeCun, Zhang and Schaul (2013) "No More Pesky Learning Rates". The interface will is 
useful for any stochastic optimization problem.

Attribution
------------

Please cite [Alcala-Burgos](http://gradworks.umi.com/35/24/3524127.html) if you find
this code useful in your research and add your paper to the 
[testimonials list](http://github.com/vidalalcala/affine-invariant-sopt/testimonial.md)

Requirements
------------

* [Armadillo library](http://arma.sourceforge.net/) 

Running
-------

    $ make
	$ ./sopt_olsTestQuadratic
