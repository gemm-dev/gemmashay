/*
This code allows for the input of some suitable parameters and calls the
numerical and differentiation and integration routines you have written.
It can be used to experiment with the accuracy of various algorithms for
numerical differentiation and integration, and to be sure your functions
are working properly.

The testing code is a little confusing because it makes use of pointers
in an unusual way (pointer-to-a-function).  This is what makes it
possible to pass a generic function to the functions you write.

To use this code with the functions you write, add them both to the same 
Pelles C project.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

double forward_diff(double (*fn)(double), double x, double delta);
double center_diff(double (*fn)(double), double x, double delta);
double second_deriv(double (*fn)(double), double x, double delta);
double trap_integrate(double (*fn)(double), double x0, double x1, int n);
double simpson_integrate(double (*fn)(double), double x0, double x1, int n);
double evolve_decay(double N, double lambda, double dt, int nsteps);

int main(int argc, char **argv)
{
  double (*fn)(double);
  double x, delta, x0, x1;
  double exact_deriv, exact_sec_deriv, exact_integral, exact_decay, result;
  double N, lambda, dt;
  int n, nsteps;
  char c;

  fn = &cos;

  x = 3./4;
  x0 = 3./4.;  x1 = 3./2.;

  exact_deriv = -sin(x);
  exact_sec_deriv = -cos(x);
  exact_integral = sin(x1)-sin(x0);
 
  printf("\nEnter 'd' to differentiate, 'i' to integrate, 'r' for radioactive decay, or 'q' to quit: ");
  scanf("%c", &c);

  while (c!='q') {
    if (c=='d') {
      printf("\nEnter the step size: ");
      scanf("%lf", &delta);

      printf("Exact derivative of fn(x) = %lf\n", exact_deriv);
      result = forward_diff(fn, x, delta);
      printf("Forward Difference = %lf\terror/delta = %lf\n", result, 
	     (result-exact_deriv)/delta);
      result = center_diff(fn, x, delta);
      printf("Centered Difference = %lf\terror/delta^2 = %lf\n", result, 
	     (result-exact_deriv)/(delta*delta));

      printf("\nExact 2nd derivative of fn(x) = %lf\n", exact_sec_deriv);
      result = second_deriv(fn, x, delta);
      printf("Approximate 2nd derivative = %lf\terror/delta^2 = %lf\n", result,
	     (result-exact_sec_deriv)/(delta*delta));
    }
    else if (c=='i') {
      printf("\nNumber of subdivisions: ");
      scanf("%d", &n);

      delta = (x1-x0)/(double)n;
      printf("Exact integral of fn(x) = %lf\n", exact_integral);
      result = trap_integrate(fn, x0, x1, n);
      printf("Trapezoidal Integral = %lf\t\terror/delta^2 = %lf\n", result,
	     (result-exact_integral)/(delta*delta));
      result = simpson_integrate(fn, x0, x1, n);
      printf("Simpson Rule Integral = %lf\terror/delta^4 = %lf\n", result, 
	     (result-exact_integral)/pow(delta,4));
    }
    else if(c=='r') {
      printf("\nInitial amount of matter: ");
      scanf("%lf", &N);
      printf("Decay rate: ");
      scanf("%lf", &lambda);
      printf("Time step interval: ");
      scanf("%lf", &dt);
      printf("Number of steps to evolve: ");
      scanf("%d", &nsteps);

      exact_decay = N*exp(-lambda*(double)nsteps*dt);
      printf("Exact N(t) = %lf\n", exact_decay);
      N = evolve_decay(N, lambda, dt, nsteps);
      printf("From Euler evolution N(t) = %lf\terror/(nsteps*dt^2) = %lf\n", N,
	     (N-exact_decay)/((double)nsteps*dt*dt));
    }

    scanf("%c", &c);   /* flush the carraige return */
    printf("\nEnter 'd' to differentiate, 'i' to integrate, 'r' for radioactive decay, or 'q' to quit: ");
    scanf("%c", &c);
  }
	
  printf("\n");
}
