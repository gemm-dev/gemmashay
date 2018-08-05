#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*

This assignment is to write the code for a few subroutines and
functions that will be used to simulate the motion of point-like
objects subject to their mutual gravitational attraction.  For
simplicity, we will only consider systems where all the motion is
confined to a two-dimensional x-y cartesian plane.

Before turning to the specifications of functions and subroutines, let
me comment about the units that we will be using.  We will use
geocentric units for the simulation program.  There is nothing special
about them and any other set of units could be used, and you could
proceed to solving the assignment without paying any attention to the
definition of the units.  However, if you wish to give a meaning to
the numbers that the simulation produces, you should read the
paragraphs immediately below.

Distances will be measured in units of the earth radius (approx. 6370
km), masses will be measured in units of the earth mass and intervals
of time will be measured in hours.

To obtain the gravitational constant G in these units, we must do a
little work.  Assume the average acceleration of gravity at the
surface of the earth is 9.8 m/s^2.  We can then calculate the value of
the acceleration of due to gravity for two point objects using the
formula for the gravitational force

       F(1,2) in absolute value =  G * m(1)*m(2) / r(1,2)^2.

m(1)=1 and r(1,2)=1 (in our units) must produce an acceleration

a(2) = F(1,2)/m(2) = G = 9.8 m/sec^2 = 9.8 * (1./6.37e6)/((1./3600)^2),

where the last equality follows from expressing 1m in units of the
earth radius and 1sec in units of hours.  Substituting we find

                      G = 19.94.

We use a #define statement below to specify this parameter.  We also
specify the maximum possible number of objects (NMAX) and the
dimensions (NDIM) in the same manner, as well as RMIN, which we will
discuss in the potential energy function.
*/

#define G 19.94
#define NMAX 20
#define NDIM 2
#define RMIN 0.1

/*
Center of mass position.  This function receives the number of objects
N, the masses of the point objects in the array mass[NMAX], their x
and y coordinates in the position array r[NMAX][NDIM], and a yet to be
calculated value for the center of mass vector rcm[NDIM].  To be
specific about the arrays, the index of the mass array refers to which
object, ie. mass[0] refers to the mass of the zeroth object.  For the
position array, the first index refers to which object, while the
second index refers to which coordinate, either x or y.  Hence the
position r[3][0] refers to the x-position of the fourth object, while
r[3][1] refers to the y-position.

Note that since N<=NMAX, there there will generally be elements of the
arrays that are unused.  Thus be sure your loops over array elements
only go up to N.  We do this to avoid the dynamic allocation of
arrays, since we do not know a priori how large N will be.  For more
complex codes where wasted memory is more of an issue, proper dynamic
allocation should be done.

Your function must calculate the coordinates in vector format of the
center of mass position.  The means you calculate the center of mass
using the rcm array that has been passed to this function.  

Note that this is NOT a function, because it does not return a value --
hence the data type "void".  This is because unfortunately C does not
allow functions to return arrays.  However, any changes made to the
array passed to the subroutine will be retained in the calling routine.
Thus an explicit "return" statement is not required.

Finally, not that this subroutine can also be used to obtain center of
mass velocity simply by passing the velocities instead of the positions.
The testing code takes advantage of this fact.
*/

void center_of_mass(int N, double mass[NMAX], double r[NMAX][NDIM], 
		    double rcm[NDIM]) 
{

}


/*
Kinetic energy.  This functions receives N, the mass[NMAX], and
v[NMAX][NDIM] and must return the kinetic energy of the system.
Recall that kinetic energy is defined by

KE = 1/2 * m * v (dot) v
*/

double kinetic_energy(int N, double mass[NMAX], double v[NMAX][NDIM])
{

}

/*
Potential energy.  This functions receives the variables N,
mass[NMAX], and r[NMAX][NDIM] and must return the potential energy of
the system.  In the expression for the potential energy the
gravitational interaction must be cut-off below a definite minimum
value of the separation RMIN=0.1 in order to avoid singularities if
two of the objects accidentally come too close.  Thus, define
rij=sqrt((r[i][0]-r[j][0])*(r[i][0]-r[j][0])+((r[i][1]-r[j][1])*(r[i][1]-r[j][1])))
if the sqrt is <= RMIN, rij=RMIN otherwise, then the potential energy
is given by the sum over all i from 0 to N-1 and all j from i+1 to N of

-G * m[i]*m[j] / rij .
*/

double potential(int N, double mass[NMAX], double r[NMAX][NDIM])
{

}
 
/*
Second-order Runge-Kutta integration algorithm. This subroutine
receives the variables N, mass[NMAX], r[NMAX][NDIM], v[NMAX][NDIM],
the number of steps nsteps and the value of the time step dt.  This
subroutine must implement nsteps steps of the Runge-Kutta method.
Recall that in the second-order Runge-Kutta method, coordinates and
velocities are first evolved to the mid-point of the interval, i.e.,
their values after dt/2 are calculated, and subsequently these values,
equated to the central derivatives, are used to evolve the variables
from the beginning to the end of the interval of duration dt.

Your routine will integrate Newton's equations of motion, namely

   dr[i][k]/dt = v[i][k]       dv[i][k]/dt = f[i][k]/m

Using the potential energy given above, the force on object i in
direction k due to object j is given by:

f[i][k] = - G * mass[i]*mass[j] * (r[i][k]-r[j][k]) / rij^3 

where rij is the scalar magnitude of the separation of i and j.  If rij
>= RMIN, we use the above expression; if rij < RMIN, we set f[i][k] = 0,
to be consistant with our definition of the energy.  The acceleration of
i is simply f[i][k]/mass[i].

It is convenient and speeds things up to recognize that the the force on
i due to j, denoted fij = -fji --- better known as Newton's third law.
In other words, once you know the force on i due to j, you get the force
on j due to i, so there is no reason to repea the calculation.  However,
you may find it easier in your coding not to take advantage of this
fact.

Depending on your approach, you will need a temporary array for the
positions, velocoties, or accelerations of the objects.  You can
declare such a multidimensional array by something like
'double r_temp[NMAX][NDIM]' --- note the use of NMAX!

Please notice: this subroutine, like the ones that follow, must implement
exactly the specified method of integration, with all the approximations
it entails, because the testing program may check, by taking dt large,
that the error is as expected.
 
*/

void move_runge_kutta(int N, double mass[NMAX], double r[NMAX][NDIM], 
		      double v[NMAX][NDIM], int nsteps, double dt)
{

}

/*
Velocity-Verlet integration algorithm. This subroutine receives the
variables N, mass[NMAX], r[NMAX][NDIM], v[NMAX][NDIM], the number of
steps nsteps and the value of the time step dt.  This subroutine must
implement nsteps steps of the velocity-Verlet method.  Please see the
comments of the Runge-Kutta method above for the definition of the forces
and accelerations.  Recall that in the velocity verlet the positions
are first evolved using the velocity and acceleration at the start of
the interval.  Then the velocities are updated using the mean
accleration at the beginning and end of the interval.
*/

void move_velocity_verlet(int N, double mass[NMAX], double r[NMAX][NDIM], 
			  double v[NMAX][NDIM], int nsteps, double dt)
{

}
