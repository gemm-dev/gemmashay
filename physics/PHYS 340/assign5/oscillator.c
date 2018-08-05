#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* function declarations */
void move_euler(double *theta, double *theta_dot, double dt, double omega0sq,
		double gamma, int system);
void move_runge_kutta(double *theta, double *theta_dot, double dt, 
                      double omega0sq, double gamma, int system);


int main(int argc, char **argv) {
  double theta, theta_dot;
  double theta_start, theta_dot_start, omega0sq, dt;
  double Q, gamma, omega_drive, drive_ampl;
  int n, nsteps, system;
  FILE *fp;

  printf("\nMOTION OF PENDULUM\n\n");
  printf("We set the ratio omega0^2 = g/l = 9 s^-1 (approximately 1m pendulum);\n");
  printf("We also choose to start the pendulum from rest (theta_dot = 0)\n\n");
  omega0sq = 9.;
  theta_dot_start = 0;

  printf("Enter the initial pendulum angle in radians (theta): ");
  scanf("%lf", &theta_start);
  printf("Enter incremental time step in seconds (dt): ");
  scanf("%lf", &dt);
  printf("Enter number of integration steps (nsteps): ");
  scanf("%d", &nsteps);
  printf("System type;\n\t1 for small angle approximation;"); 
  printf("\n\t2 for no approximation;"); 
  printf("\n\t3 for damped with no approximation: "); 
  scanf("%d", &system);

  /* extra information needed if we have damping */
  if (system==3) {
    printf("\n\tWe determine the damping (gamma) from the quality factory Q = omega0/gamma\n");
    printf("\tRecall that Qcritial = 0.5; Q > 0.5 is under-damped\n");
    printf("\tEnter quality factor (Q): ");
    scanf("%lf", &Q);
    gamma = sqrt(omega0sq)/Q;
    /* if we wanted to add a drive, we could use the following */
    /*
    printf("Enter driving frequency (omega_drive): ");
    scanf("%lf", &omega_drive);
    printf("Enter driving amplitude (drive_ampl): ");
    scanf("%lf", &drive_ampl);
    */
  }

  fp = fopen("euler.dat", "w");

  theta = theta_start;
  theta_dot = theta_dot_start;
  for (n=0; n<nsteps; n++) {
    /* every 10 steps dump to file the current angle */
    if (n%10==0)
      fprintf(fp, "%lf\t%lf\n", (double)n*dt, theta);
    move_euler(&theta, &theta_dot, dt, omega0sq, gamma, system);
  }

  fclose(fp);

  fp = fopen("runge_kutta.dat", "w");

  theta = theta_start;
  theta_dot = theta_dot_start;
  for (n=0; n<nsteps; n++) {
    /* every 10 steps dump to file the current angle */
    if (n%10==0)
      fprintf(fp, "%lf\t%lf\n", (double)n*dt, theta);
    move_runge_kutta(&theta, &theta_dot, dt, omega0sq, gamma, system);
  }

  fclose(fp);

  printf("\nData in files euler.dat and runge_kutta.dat\n");
}

