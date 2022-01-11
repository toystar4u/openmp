#include <stdio.h>
#include <omp.h> 

/*
    $ gcc -fopenmp pi_critical.c -o pi_critical
    $ ./pi_critical

*/


static long num_steps = 100000000; 
double step;

#define NUM_THREADS 4


void main ()
{ 
    double pi, step = 1.0/(double) num_steps;

 	omp_set_num_threads(NUM_THREADS); 

 	#pragma omp parallel 
 	{ 
        long i;
        int id,nthrds;
 		double x, sum;

 		nthrds = omp_get_num_threads(); 
 		id = omp_get_thread_num(); 

 		for (i=id, sum=0.0;i< num_steps; i=i+nthrds) {
 			x = (i+0.5)*step;
 			sum += 4.0/(1.0+x*x);
 		}
		
		#pragma omp critical
        pi += sum * step;
 	}	
}
