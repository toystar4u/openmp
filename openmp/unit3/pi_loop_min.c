#include<stdio.h>
#include<omp.h>

/*
    $ gcc -fopenmp pi_loop_min.c -o pi_loop_min
    $ export OMP_NUM_THREADS=4
    $ ./pi_loop_min
*/



static long num_steps = 100000000; 
double step; 

int main () {
    long i; double x, pi, sum = 0.0; 
    //omp_set_num_threads(2);                               // no needed when environment variable applied
    step = 1.0/(double) num_steps;                      	// 𝚫x

    #pragma omp parallel for private(x) reduction(+:sum)
    for (i=0;i< num_steps; i++){ 
        x = (i+0.5)*step;                                   // xi
        sum = sum + 4.0/(1.0+x*x); 	                        // F(xi)= 4.0/(1.0+xi2); sum = ΣF(xi) 
    } 
    pi = step * sum;                                        // pi = 𝚫x*ΣF(xi) 

	
	return 0;
} 
