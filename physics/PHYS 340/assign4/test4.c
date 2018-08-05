/*
This code allows for the input of some suitable parameters and calls the
root finding algorithms we discussed in class.  Use this code to test the functions you have written.

Compile and execute the same as the previous assignment.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

double bracket_root(double (*fn)(double), double x0, double x1, double tol, 
		    int *n, int maxsteps);
double bisection_root(double (*fn)(double), double x0, double x1, double tol,
		      int *n, int maxsteps);
double newton_raphson_root(double (*fn)(double), double (*dfdx)(double),
			   double x, double tol, int *n, int maxsteps);

int main(int argc, char **argv)
{
  double (*fn)(double), (*dfdx)(double);
  double tol, x0, x1;
  double result;
  int nsteps, maxsteps;
  char c;

  fn = &sin;
  dfdx = &cos;
  maxsteps = 1e8;

  printf("\nRoot finding of sin");
  printf("\nEnter 'q' at any time to quit\n");
  printf("\nEnter '1' for Bracket, '2' for Bisection, or '3' for Newton-Raphson: ");
  scanf("%c", &c);

  while (c!='q') {
    if (c=='1') {
      printf("\nEnter the lower bound: ");
      scanf("%lf", &x0);
      printf("Enter the upper bound: ");
      scanf("%lf", &x1);
      printf("Enter the tolerance: ");
      scanf("%lf", &tol);

      result = bracket_root(fn, x0, x1, tol, &nsteps, maxsteps);
      if (result == sqrt(log(2.1)))
	printf("Invalid Bracket specified!");
      else 
	printf("Bracketed root = %lf after %d steps\n", result, nsteps);
    }
    else if (c=='2') {
      printf("\nEnter the lower bound: ");
      scanf("%lf", &x0);
      printf("Enter the upper bound: ");
      scanf("%lf", &x1);
      printf("Enter the tolerance: ");
      scanf("%lf", &tol);

      result = bisection_root(fn, x0, x1, tol, &nsteps, maxsteps);
      if (result == sqrt(log(2.1)))
	printf("Invalid Bracket specified!");
      else 
	printf("Bisection root = %lf after %d steps\n", result, nsteps);
    }
    else if (c=='3') {
      printf("\nEnter the starting value: ");
      scanf("%lf", &x0);
      printf("Enter the tolerance: ");
      scanf("%lf", &tol);

      result = newton_raphson_root(fn, dfdx, x0, tol, &nsteps, maxsteps);
      printf("Newton-Raphson root = %lf after %d steps\n", result, nsteps);
    }
    else if (c!='q') {
      printf("\n\tInvalid Input!!\n");
      exit(EINVAL);
    }


    scanf("%c", &c);   /* flush the carraige return */
    printf("\nEnter '1' for Bracket, '2' for Bisection, or '3' for Newton-Raphson: ");
    scanf("%c", &c);
  }
	
  printf("\n");
}
