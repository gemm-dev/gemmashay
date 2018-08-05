#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*

This assignment focuses on using integration methods to solve the
problem of pendulum motion.  We will use two methods: (i) Euler and (ii)
2nd order Runge-Kutta.  The results should illustrate two points; first,
you will see that the Euler method is clearly a bad method to use, as it
quickly diverges from the expected solution.  Second, you will be able
to see from the Runge-Kutta solution how the small angle approximate
analytic solution fails.

When these functions are linked with the testing code, two files will be
produced: "euler.dat" and "runge_kutta.dat".  These files contain the
angle as a function of time for each method.  By viewing the data with
something like xmgrace, you can compare with the approximate analytic
solution to see if your code is functioning correctly.

Since we always start with theta_dot = 0, the small angle approximate
solution is
			theta(t) = theta_0 * cos(omega0*t)

For the underdamped oscillator (Q = omega0/gamma > 0.5), the small angle
approximate solutions is
		theta(t) = theta_0 * exp(-gamma*t/2) * cos(omega*t)
where omega^2 = omega0^2 - (gamma/2)^2

Feel free to explore other values of Q.  You can find the small angle
solutions for over-damped and critically damped in your textbooks (like
French, from Waves).  Finally, it would be easy to explore cases like
driven oscillators simply by adding a forcing term.

*/

/* 
Euler integration of a single time step.  This subroutine receives the
pointer to the variables theta and theta_dot, as well as the ordinary
variables for the time step dt, the natural pendulum frequency (squared)
omega0sq, the damping coefficient gamma, and an integer for the system
type.  The result of the subroutine should be to update theta and
theta_dot by one time step.

We must pass theta and theta_dot as pointers so that changes in this
function will be preserved in the calling function (main, in this case).
Recall that in order to change the contents of the pointer, you use the
notation *theta and *theta_dot.  For example, to add for to theta:
	*theta += 4;

The variable system tells up which system we use:
	system = 1 for small angle approximation
	system = 2 for no approximation
	system = 3 for no approximation plus damping
The force will be different for the different values of system, so you
will need to check the value of system.
*/

void move_euler(double *theta, double *theta_dot, double dt, double omega0sq,
		double gamma, int system)
{

  double theta_old;

  if (system == 1)
  {
    theta_old = *theta;
    *theta += *theta_dot * dt;
    *theta_dot -= omega0sq * theta_old * dt;
  }

  else if (system == 2)
  {
    theta_old = *theta;
    *theta += *theta_dot * dt;
    *theta_dot -= omega0sq * sin(theta_old) * dt;
  } 

  else if (system == 3)
  {
    theta_old = *theta;
    *theta += *theta_dot * dt;
    *theta_dot -= (*theta_dot * gamma + omega0sq * sin(theta_old)) * dt;
  } 

}

/* 
2nd order Runge-Kutta integration of a single time step.  This
subroutine receives the pointer to the variables theta and theta_dot, as
well as the ordinary variables for the time step dt, the natural
pendulum frequency (squared) omega0sq, the damping coefficient gamma,
and an integer for the system type.  The result of the subroutine should
be to update theta and theta_dot by one time step.

We must pass theta and theta_dot as pointers so that changes in this
function will be preserved in the calling function (main, in this case).
Recall that in order to change the contents of the pointer, you use the
notation *theta and *theta_dot.  For example, to add for to theta:
	*theta += 4;

The variable system tells up which system we use:
	system = 1 for small angle approximation
	system = 2 for no approximation
	system = 3 for no approximation plus damping
The force will be different for the different values of system, so you
will need to check the value of system.

For the Runge-Kutta method, you will likely need to introduce extra
variables to store the values of theta and theta_dot at the half time
step.

*/

void move_runge_kutta(double *theta, double *theta_dot, double dt, 
                      double omega0sq, double gamma, int system)
{

  double theta_half, theta_dot_half;

  if (system == 1)
  {
    theta_half = *theta + *theta_dot * dt/2;
    theta_dot_half = *theta_dot - omega0sq * * theta * dt/2;
  }

  else if (system == 2)
  { 
    theta_half = *theta + *theta_dot * dt/2;
    theta_dot_half = *theta_dot - omega0sq * sin(*theta) * dt/2;
  } 

  else if (system == 3)
  {
    theta_half = *theta + *theta_dot * dt/2;
    theta_dot_half = *theta_dot - (*theta_dot * gamma + omega0sq * sin(*theta)) * dt/2;
  } 

  if (system == 1)
  {
    *theta += theta_dot_half * dt;
    *theta_dot -= omega0sq * theta_half * dt;
  }

  else if (system == 2)
  {
    *theta += theta_dot_half * dt;
    *theta_dot -= omega0sq * sin(theta_half) * dt;
  } 

  else if (system == 3)
  {
    *theta += theta_dot_half * dt;
    *theta_dot -= (theta_dot_half * gamma + omega0sq * sin(theta_half)) * dt;
  } 

  

}
