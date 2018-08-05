/*
NOTE!  The code for all these function is really simple, even trivial.
The main purpose of this part assignment is to develop some experience
with function calls and with the notion of an external function.

We want our functions to be general purpose functions that can calculate
derivatives and integrals of any given function, passed to it from the
calling program (note that it would not be very efficient to invoke a
subroutine function for an operation as simple as calculating a numerical 
derivative, but our goal here is only to exemplify some important features 
of subroutine calls, not efficiency).  For this reason, our functions
must contain the name (fn) of a generic function in their list of
arguments.  fn is a dummy name that stands for whatever function is
passed to the function subroutines by the calling program.  
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 
forward_diff function receives from the calling program the name fn of
an external function program, the argument x and the step delta
and must return as the forward difference approximation to the
derivative of the function fn calculated at x with step size delta.
*/

double forward_diff(double (*fn)(double), double x, double delta)
{

}

/* 
center_diff function receives from the calling program the name fn of
an external function program, the argument x and the step delta
and must return as the central difference approximation to the
derivative of the function fn calculated at x with step size delta
(to avoid any possible confusion, this means that fn will be evaluated
at x-delta and x+delta).
*/

double center_diff(double (*fn)(double), double x, double delta)
{

}

/*
second_deriv function receives from the calling program the name fn of
an external function program, the argument x and the step delta
and must return the approximation to the second derivative
of the function fn at x based on the values taken by fn at x and
at the nearest neighbor points x+dx, x-dx.
*/

double second_deriv(double (*fn)(double), double x, double delta)
{

}

/* 
trap_integrate function receives from the calling program the name fn of
an external function program and the lower and upper limits of an
integration domain, x0 and xn, and must return as it the approximation 
to the integral of fn over the interval x0,xn given by the trapezoidal
formula based on a subdivision of the interval of integration into n
equal subintervals.
*/

double trap_integrate(double (*fn)(double), double x0, double xn, int n)
{

}
 
/*
simpson_integrate function receives from the calling program the name fn of
an external function program and the lower and upper limits of an
integration domain, x0 and xn, and must return the approximation 
to the integral of fn over the interval x0,xn given by Simpson's
formula based on a subdivision of the interval of integration into 
2*n equal subintervals.
*/

double simpson_integrate(double (*fn)(double), double x0, double xn, int n)
{
      
}

/*
evolve_decay receives from the calling program the initial mass of
matter M, the decay rate lambda, the time step dt, and the number of
steps nsteps to evolve the system.  The function should then evolve M by
nsteps steps using the Euler method, and return the final value of M.
*/
double evolve_decay(double M, double lambda, double dt, int nsteps)
{

}
