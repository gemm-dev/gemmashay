#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// The golden ratio
#define G 0.3819660112501051

/* 
Coarse bracketing of a 1D function minimum from an arbitrary starting point.
From the calling program, this function receives 
- the function fn(x) being minimized
- the point where to start your search (start)
- an array bracket[3] with three elements that will store the bracketing 
points, given by the end points (elements 0 and 2) and a point between (element 1)
- the step size over which to search for a minimum
- the maximum number of iterations maxit to allow (also prevents infinite 
loops)

From the starting point, you decide the downhill direction and search downward
to find three points to bracket the minimum.  If searching forward, the 
first three candidate points are 
start, start + step, and start + 2.*step

Assuming these do not bracket the root, the next candidate points are
start + step, start + 2.*step, and start + 3.*step

And so on for subsequent steps.  When the midpoint is smaller than the two 
endpoints, you have bracketed the minimum.

Put the values of these three points in the array bracket[3] in INCREASING order.  
In other words, you must order the values so that  
bracket[0]<bracket[1]<bracket[2].
This will be important for our golden section search.  Since bracket is
an array, the values do not need to be explicitly returned.  This is why the 
function is of type void.

Be sure not to exceed the maximum number of iterations while searching.
*/


void bracket_min(double (*fn)(double), double start, double bracket[3], 
		 double step, int maxit)
{

}

/* 
Golden section search for the minimum of a 1-D function.  From the calling 
program, the function receives
- the function fn(x) being minimized
- the points a, b, and c that bracket the minimum
- the tolerance for the range of the minimum location
- the maximum number of allowed iterations (maxit) to search

We have already defined the golden ratio, given by G (see the #define
at the top of the file).

When you have narrowed the range of the minimum location to within tol
(or if you exceed the maximum number of iterations), return the
midpoint of that range.
*/

double golden_section(double (*fn)(double), double a, double b, double c,
		      double tol, int maxit)
{

}
