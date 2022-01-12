
#include <stdio.h>
#include<omp.h>

/*
    $ gcc -fopenmp ex1.c -o ex1
    #$ export OMP_NUM_THREADS=4
    $ ./ex1

*/

int main() { 

    #pragma omp parallel
    {

        int ID = omp_get_thread_num();

        printf(" hello(%d) ", ID); 
        printf(" world(%d) \n", ID); 
    }

    return 0;
}
