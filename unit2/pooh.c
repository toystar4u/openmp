#include <stdio.h>
#include <omp.h> 

/*
    $ gcc -fopenmp pooh.c -o pooh
    $ export OMP_NUM_THREADS=4
    $ ./pooh
*/


void pooh(int id, double *dummy)
{
    printf("pooh: %d\n",id);
}

void main()
{
    double A[1000]; 

    omp_set_num_threads(4); 
    #pragma omp parallel 
    { 
        int ID = omp_get_thread_num(); 
        pooh(ID,A); 
    }
    
    printf("all done\n");
}
