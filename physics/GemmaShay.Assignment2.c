#include <stdio.h>
#include <stdlib.h>
#include <math.h

int main(int argc , char **arg)
{
	double x,t;
	printf ("Enter an exponent");
		scanf ("%lf",&x);
	printf ("Enter tolerance between 0 and 1");
		scanf ("%lf",&t);

	double ExpArray[100];
	
	int n;
	
	for ( n = 1; n < 100; n++ )
	{
		ExpArray[n]=ExpArray[n-1]*x/n;
		
	}		
	double sum = 0.;
	n=0;
	while ( t < error )
	{
		sum +=  ExpArray[n];
		double error = fabs((sum - exp(n))/exp(n);
		n++;
 }
                            }
  
   
  

