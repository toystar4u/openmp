
#include <stdio.h>
#include <omp.h>
#include <math.h>

#include "random.h"

/*
    $ gcc -fopenmp pi_mc.c random.c -o pi_mc
    $ export OMP_NUM_THREADS=4
    $ ./pi_mc
*/

static long num_trials = 100000000;
static double exact_pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;

int main ()
{
    long i; 
    long Ncirc = 0; 
    double pi, x, y;
    double r = 1.0; 				            // radius of circle. Side of square is 2*r 
    
    //seed(0,-r, r); 				            // The circle and square are centered at the origin
    seed(); 				                    // The circle and square are centered at the origin

    #pragma omp parallel for private (x, y) reduction (+:Ncirc)
    for(i=0;i<num_trials; i++){
        x = random(); 
        y = random();
        if(( x*x + y*y) <= r*r) Ncirc++;
    }

    pi = 4.0 * ((double)Ncirc/(double)num_trials);
    printf("\n %ld trials, pi is %f, error=%e\n",num_trials, pi, fabs(pi-exact_pi));

    return 0;
}
