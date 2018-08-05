#include <GL/glut.h>
#include <math.h>

#define NMAX 20
#define NDIM 2

void plot2d(int N, int size, double scale, double rold[NMAX][NDIM], 
	    double r[NMAX][NDIM])
{
  int i, x, y;

  /* Clear window, color material */
  /*glClear(GL_COLOR_BUFFER_BIT);*/
  for (i=0; i<N; i++) {
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
  }

  glutSwapBuffers();
  glutMainLoopEvent();
}

/* Initialize window position, title, and display list */

void init_window(int size, int *argc, char **argv)
{
  glutInitWindowSize( size, size );
  glutInit(argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutCreateWindow( "Gravitational Trajectories" );  
  glClearColor(0.3, 0.3, 0.3, 0.0);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, size-1, 0, size-1, -1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
  glutMainLoopEvent();
}
