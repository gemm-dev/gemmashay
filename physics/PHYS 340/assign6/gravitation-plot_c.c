
/*
This code tests the functions and subroutines you have written
associated with integrating the equations of motions for N bodies
interacting via gravitational forces.

Compile and execute the same as the previous assignments.

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <time.h>

#define NMAX 20
#define NDIM 2

void center_of_mass(int N, double mass[NMAX], double r[NMAX][NDIM], 
		    double rcm[NDIM]);
double angular_mom(int N, double mass[NMAX], double r[NMAX][NDIM], 
		   double v[NMAX][NDIM]);
double kinetic_energy(int N, double mass[NMAX], double v[NMAX][NDIM]);
double potential(int N, double mass[NMAX], double r[NMAX][NDIM]);
void move_velocity_verlet(int N, double mass[NMAX], double r[NMAX][NDIM], 
		double v[NMAX][NDIM], int nsteps, double dt);
void move_runge_kutta(int N, double mass[NMAX], double r[NMAX][NDIM], 
		      double v[NMAX][NDIM], int nsteps, double dt);

void init_window(int size, int *argc, char **argv);
void plot2d();

int N, size;
double scale;
double rold[NMAX][NDIM];
double r[NMAX][NDIM];
int i, k;
  int t1, n_draw, n_per_draw, nsteps;
  double v[NMAX][NDIM], mass[NMAX];
  double rcm[NDIM], vcm[NDIM];
  double kin, pot, dt;
  char answer;

int main(int argc, char **argv)
{
  
  FILE *fp;

  printf("Do you wish to read initial positions from a data file? ");
  scanf("%c", &answer);
  if (answer == 'y' || answer == 'Y') {
    if ((fp=fopen("gravity.dat", "r"))==NULL) {
      printf("Could not open file gravity.dat");
      exit(0);
    }

    fscanf(fp, "%d", &N);
    /*
    mass = (double*) calloc(N, sizeof(double));
    r = (double**) calloc(N, sizeof(double*));
    v = (double**) calloc(N, sizeof(double*));
    for (i=0; i<N; i++) {
      r[i] = (double*) calloc(NDIM, sizeof(double));
      v[i] = (double*) calloc(NDIM, sizeof(double));
    }
    */
    for (i=0; i<N; i++) {
      fscanf(fp, "%lf", &mass[i]);
      for (k=0; k<NDIM; k++) {
	fscanf(fp, "%lf", &r[i][k]);
      }
      for (k=0; k<NDIM; k++) {
	fscanf(fp, "%lf", &v[i][k]);
      }
    }
  }
  else {
    N = NMAX+1;
    while (N>NMAX || N<1) {
      printf("Enter the number of objects (<%d) you would like to simulate: ",
	     NMAX);
      scanf("%d", &N);
      if (N>NMAX || N<1) 
	printf("Invalid number of objects; try again.\n");
    }
    /*
    mass = (double*) calloc(N, sizeof(double));
    r = (double**) calloc(N, sizeof(double*));
    v = (double**) calloc(N, sizeof(double*));
    for (i=0; i<N; i++) {
      r[i] = (double*) calloc(NDIM, sizeof(double));
      v[i] = (double*) calloc(NDIM, sizeof(double));
    }
    */
    for (i=0; i<N; i++) {
      printf("\tObject %d mass:", i);
      scanf("%lf", &mass[i]);

      printf("\tObject %d position:\n", i);
      for (k=0; k<NDIM; k++) {
	printf("\t\tcoordinate %d: ", k);
	scanf("%lf", &r[i][k]);
      }

      printf("\tObject %d velocity:\n", i);
      for (k=0; k<NDIM; k++) {
	printf("\t\tcoordinate %d: ", k);
	scanf("%lf", &v[i][k]);
      }
    }
  }

  /* rescale coordinates to that the center of mass is fixed */
  printf("\nRescaling positions and velocities so that the\n");
  printf("center of mass is fixed at the origin\n");
  center_of_mass(N, mass, r, rcm);
  center_of_mass(N, mass, v, vcm);
   
  for (i=0; i<N; i++) {
    for (k=0; k<NDIM; k++) {
      r[i][k] -= rcm[k];
      v[i][k] -= vcm[k];
    }
  }

  scanf("%c", &answer);       /* flush the carraige return */
  printf("Enter 'r' for Runga Kutta, or 'v' for velocity Verlet: ");
  scanf("%c", &answer);

  printf("Time step dt: ");
  scanf("%lf", &dt);
  printf("Number of time steps: ");
  scanf("%d", &nsteps);
  printf("Enter scale factor for drawing (around 20): ");
  scanf("%lf", &scale);
  n_per_draw = 100;
  n_draw = nsteps/100;
  /*
  printf("Number of time steps for each drawing of the trajectory: ");
  scanf("%d", &n_per_draw);
  printf("Number of times to draw: ");
  scanf("%d", &n_draw);
  */
  printf("\nINITIAL CONDITIONS:\n");
  center_of_mass(N, mass, r, rcm);
  center_of_mass(N, mass, v, vcm);

  printf("\tCOM position: %lf %lf\n", rcm[0], rcm[1]);
  printf("\tCOM velocity: %lf %lf\n", vcm[0], vcm[1]);
  /*  printf("\tAngular momentum: %lf\n", angular_mom(N, mass, r, v));*/
  kin = kinetic_energy(N, mass, v);
  pot = potential(N, mass, r);
  printf("\tEnergies:\n\tKinetic: %lf\n\tPotential: %lf\n\tTotal: %lf\n",
	 kin, pot, kin+pot);

 printf("\nFINAL STATE:\n");
  center_of_mass(N, mass, r, rcm);
  center_of_mass(N, mass, v, vcm);

  printf("\tCOM position: %lf %lf\n", rcm[0], rcm[1]);
  printf("\tCOM velocity: %lf %lf\n", vcm[0], vcm[1]);
  /*  printf("\tAngular momentum: %lf\n", angular_mom(N, mass, r, v));*/
  kin = kinetic_energy(N, mass, v);
  pot = potential(N, mass, r);
  printf("\tEnergies:\n\tKinetic: %lf\n\tPotential: %lf\n\tTotal: %lf\n",
	 kin, pot, kin+pot);



 size = 600;
  init_window(size, &argc, argv);


  /*for (t1=0; t1<n_draw; t1++) {

    for (i=0; i<N; i++) 
      for (k=0; k<NDIM; k++)
	rold[i][k] = r[i][k];


    if (answer=='r')
      move_runge_kutta(N, mass, r, v, n_per_draw, dt);
    else if (answer=='v')
      move_velocity_verlet(N, mass, r, v, n_per_draw, dt);
    plot2d();
  }
  */
    
 

 
}

void plot2d()
{
  int x, y;

  /* Clear window, color material */
  /*glClear(GL_COLOR_BUFFER_BIT);*/

for (t1=0; t1<n_draw; t1++) {
    for (i=0; i<N; i++) 
      for (k=0; k<NDIM; k++){
	      rold[i][k] = r[i][k]; 
        if (answer=='r')
          move_runge_kutta(N, mass, r, v, n_per_draw, dt);
        else if (answer=='v')
          move_velocity_verlet(N, mass, r, v, n_per_draw, dt);
        glBegin(GL_LINE_STRIP);
        glColor3f((i%3==0), (i%3==1), (i%3==2));
        x = size/2+scale*rold[i][0];
        y = size/2+scale*rold[i][1];
        glVertex2i(x,y);
        x = size/2+scale*r[i][0];
        y = size/2+scale*r[i][1];
        glVertex2i(x,y);
        glFlush(); 
        glEnd();
        glutSwapBuffers(); 
        Sleep(10);}
} }

/* Initialize window position, title, and display list */

void init_window(int size, int *argc, char **argv)
{
  glutInit(argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize( size, size );
  glutInitWindowPosition(100,100); //PT
  glutCreateWindow( "Gravitational Trajectories" );  
  glClearColor(0.3, 0.3, 0.3, 0.0);
  glColor3f(0.0, 0.0, 1.0);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, size-1, 0, size-1, -1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
  glutDisplayFunc(plot2d);
  glutMainLoop(); //PT

  return 0;
}
