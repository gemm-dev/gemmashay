#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 
Bracket method of root finding.  This function receives from the
calling program the name fn of an external function program, the
endpoints x0 and x1 that provide an initial bracket of the root of the
function, the tolerance tol for your estimate of the root, a pointer
to n, the number of steps needeed to coonverge, and the maximum number
of steps maxsteps to allow.  Your function should return the estimate
of the root using the bracket method.  Return the midpoint of the
range to which you have bracketed the root.

You are also required to keep a count of the number of steps for your
root to converge.  We will call this variable 'nsteps'; you will see it
is already decleared.  The function will return the number of steps
needed by using a pointer.  Pointers can be confusing, so to keep things
simple, you can return your count by placing the following line
immediately prior to any return statement:

      *n = nsteps;

If the number of steps reaches maxsteps, you should stop searching and
return your current estimate.  This is to avoid unintended infinite loops.
You may assume that x1>x0 -- otherwise you would need to check.
*/


double bracket_root(double (*fn)(double), double x0, double x1, double tol,
		    int *n, int maxsteps)
{
  int nsteps = 0;
  double fi;
  double ftest;

  fi=fn(x0);

  do{
    nsteps++;
    ftest = fn(x0)*fn(x0+tol*(double)nsteps);
  }
  while(ftest > 0 && nsteps < maxsteps);

  *n = nsteps;
  return(x0+tol*(nsteps-0.5));
}

/* 
Bisection method of root finding.  This function receives from the
calling program the name fn of an external function program, the
endpoints x0 and x1 that bracket the root of the function, the
tolerance tol for your estimate of the root, a pointer to n, the
number of steps needeed to coonverge, and the maximum number of steps
maxsteps to allow. Your function should return the estimate of the
root using the bisection method.  Return the midpoint of the range to
which you have bracketed the root.

You are also required to keep a count of the number of steps for your
root to converge.  We will call this variable 'nsteps'; you will see it
is already decleared.  The function will return the number of steps
needed by using a pointer.  Pointers can be confusing, so to keep things
simple, you can return your count by placing the following line
immediately prior to any return statement:

      *n = nsteps;

If the number of steps reaches maxsteps, you should stop searching and
return your current estimate.  This is to avoid unintended infinite loops.
You may assume that x1>x0 -- otherwise you would need to check.
*/

double bisection_root(double (*fn)(double), double x0, double x1, double tol, 
		      int *n, int maxsteps)
{
  int nsteps = 0;
  double xmid;

  while(x1-x0 > tol && nsteps < maxsteps)  {
    nsteps++;
    xmid = (x0+x1)/2;
    if(fn(xmid) == 0) {
      *n = nsteps;
      return(xmid);
    }

    if(fn(x0)*fn(xmid) < 0)
      x1 = xmid;
    else
      x0 = xmid;
  }

  *n = nsteps;
  return((x0+x1)/2);

}


/* 
Newton-Raphson method of root finding.  This function receives from
the calling program the name fn of an external function, the
derivative dfdx of that function, the starting point x, the tolerance
tol for your estimate of the root, a pointer to n, the number of steps
needed to coonverge, and the maximum number of steps maxsteps to
allow. Your function should return the estimate of the root using the
Newton-Raphson method.  Return your final estimate for the root, NOT
the midpoint of the last two estimates (as you did for the previous
methods).

You are also required to keep a count of the number of steps for your
root to converge.  We will call this variable 'nsteps'; you will see it
is already decleared.  The function will return the number of steps
needed by using a pointer.  Pointers can be confusing, so to keep things
simple, you can return your count by placing the following line
immediately prior to any return statement:

      *n = nsteps;

If the number of steps reaches maxsteps, you should stop searching and
return your current estimate.  This is to avoid unintended infinite loops.

To complete this function, you will likely need the absolute
value function, which is fabs(x).
*/

double newton_raphson_root(double (*fn)(double), double (*dfdx)(double),
			   double x, double tol, int *n, int maxsteps)
{
  int nsteps = 1;
  double x1 = x - fn(x)/dfdx(x); 

  while(fabs(x1-x)>tol && nsteps < maxsteps)  {
    nsteps++;
    x = x1;
    x1 = x - fn(x)/dfdx(x); 
  }

  *n = nsteps;
  return x1;

}
