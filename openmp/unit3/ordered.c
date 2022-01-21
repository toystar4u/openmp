
#include <stdio.h>
#include <omp.h>


/*
    gcc -fopenmp ordered.c -o ordred
    ./ordered

*/


float work(int i)
{
    int id = omp_get_thread_num();
    return (float)i*id;
}

void main(){
    int i;
    int N=20;

    #pragma omp parallel for ordered	        // parallel 
    //#pragma omp for ordered	                            // single thread
    for(i=0; i<N; i++){	
    float res = work(i);	
    #pragma omp ordered	                            // ordered construct
    {	
        printf("result	for %d	was %f\n", i, res);	
        fflush(stdout);	
    }	
  }
}
