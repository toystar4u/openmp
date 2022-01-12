
#include "random.h"
#include <omp.h>


static long MULTIPLIER = 1366; 
static long ADDEND = 150889; 
static long PMOD = 714025; 
long random_last = 0; 

#define MAX_THREADS 128
unsigned long long  pseed[MAX_THREADS];

#pragma omp threadprivate(random_last) 

void seed( )
{
    int i, j, id, nthreads, iseed;
    long mult_n ;
    id = omp_get_thread_num();

    #pragma omp single 
    { 
        nthreads = omp_get_num_threads(); 
        iseed = PMOD/MULTIPLIER; 		// just pick a seed 
        pseed[0] = iseed; 
        mult_n = MULTIPLIER; 

        for (i = 1; i < nthreads; ++i) { 
            iseed = (unsigned long long)((MULTIPLIER * iseed) % PMOD); 
            pseed[i] = iseed; 
            mult_n = (mult_n * MULTIPLIER) % PMOD; 
        }
    }

    random_last = (unsigned long long) pseed[id]; 
}



double random () { 
    long random_next; 
    random_next = (MULTIPLIER * random_last + ADDEND)% PMOD; 
    random_last = random_next; 

    return ((double)random_next/(double)PMOD); 
}
