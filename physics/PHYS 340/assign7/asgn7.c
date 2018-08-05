#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double shoot(double energy, int nsteps, double *psi);

/*
This assignment consists of writing three functions to implement the
shooting method for solving of the Schrodinger equation

	-hbar^2/(2m) gradient^2 psi + V(x,y,..) psi = E psi

where psi is the wave function, V is the potential energy function, and
E are the energy eigenvalues that solve the equation.  The goal of this
assignment is to determine the wave function and energy that solves the
Schrodinger equation.

For the simplicity, we will limit ourselves to solving the case where
the potential is that of a particle-in-a-box in 1-dimension --- in other
words

		/
		| Infinity	x <= 0
	V(x) =  | 0		0 < x < L
		| Infinity	x >= L
		\

It is convenient to use "Planck" units for the calculation.  In Planck
units, hbar = c = G = k (Coulomb constant) = 1.  In addition, we will
take the particle in the box to me an electron, and measure mass in
units of electron mass, and so the mass = 1 for this case.  Similarly, we
can take the size of the box the be L=1, without loss of generality.

The shooting method is designed for "boundary value problems".
Accordingly, we must specify the values of psi(0) and psi(L) (ie at the
boundaries).  For this problem, the boundary conditions are simply
psi(0) = psi(L) = 0.

Upon completion, the code will print the energy found and the energy of
the nearest eigenstate of the exact solution, given by E = 1/2*(n*Pi)^2
in our units.  The code will also print the wave function in the file
psi.dat so that you can plot it.

While we will limit ourselves to the particle-in-a-box, you're code
could be easily adapted to more complex problems simply by changing V(x)
-- for example to the potential of a hydrogen atom.  The only tricky
part is that boundary conditions become more complex.  In the case of
the hydrogen atom, you specify the conditions at r = 0 and r ->
Infinity.  To avoid the infinity, you would take advantage of the fact
that in the large r limit, you can solve the an approximate Schrodinger
equation exactly, and hence use as the boundary condition as the exact
approximate solution at some large value of r.
*/

/* 
The function bracket_energy receives the starting energy, the energy
step de, the number of lattice sites nsteps, and an array psi that will
contain the wave function returned by the function shoot.  The purpose
of the function is to find the values of energy and energy+de that
bracket the energy which solves the Schrodinger equation.  The function
should return the starting value of the energy range by using the simple
bracket method.
*/

double bracket_energy(double energy, double de, int nsteps, double *psi)
{
}

/*
The function bisect_energy receives the energies e0 and e1 that bracket
the energy that solves the Schrodinger equation, the tolerance tol for
the final energy, the number of lattice sites nsteps, and an array psi
that will contain the wave function returned by the function shoot.  The
function should return the value of energy that solves the Schrodinger
equation using the simple bisection method.
*/

double bisect_energy(double e0, double e1, double tol, int nsteps, double *psi) 
{
}

/* 
The function shoot receives the guess for the energy that solves the
Schrodinger equation, the number of lattice sites nsteps, and an array
psi in which you should store the wave function.  The simplest version
of the shooting method works by starting with the value at one of the
boundaries, and integrating to the opposite boundary using the guess for
energy.  The function should return the difference between the value at
the opposite boundary and the expected value at the boundary.  When that
difference is zero, we have the correct solution.

The Schrodinger equation is a second order differential equation.  To
solve with the shooting method, you must either recast it as two coupled
differential equations and use a method like Runge-Kutta, or use a
method specifically designed for second order differential equations.
We will do the latter, and use the Numerov-Cowling method (discussed in
class) to integrate.

Recall that the Numerov-Cowling method allows you to calculate psi(x+dx)
given the values psi(x) and psi(x-dx).  At the beginning of the
integration, we have only the value at the boundary, say psi(0) = 0 if
you start from the left boundary.  Hence we also need an expression for
psi(dx) to start up the algorithm.  We can arbitrarily choose psi(dx) =
1.  This will result in an un-normalized wave function.  When we satisfy
the opposiste boundary condition, we will use another function to impose
the normalization.

Be careful to ensure that you integrate all the way up to the second
boundary at x=L=1. To do this, your loop over lattice sites must start
from zero and go up to (and include) nsteps.  The answer will be
sensitive to this.  Also remember to store the calculated values of psi
in the array provided.
*/

double shoot(double energy, int nsteps, double *psi)
{
}


/* 
The function normalize recieves the wave function psi and the number of
array elements nsteps of the array psi.  The purpose of the function is
to enforce the quantum normlization condition, i.e. integral |psi^2| =
1, where the integral is over the limits 0 to 1 in this case.  Note that
the array psi actually extends up to nsteps+1 because we include the
boundary at x=1.

Using the trapezoidal rule, calculate integral |psi^2|, and use the
square root of the result to normalize psi.
*/

void normalize(double *psi, int nsteps) 
{
}
