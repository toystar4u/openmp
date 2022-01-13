#include <omp.h>
#include <stdio.h>



/*
    $ gcc -fopenmp nested.c -o nested

    # 1) no options
    $ ./nested

    # 2)
    $ export OMP_NESTED=true
    $ export OMP_MAX_ACTIVE_LEVELS=3
    $ ./nested


*/


void report_num_threads(int level)
{
    #pragma omp single 
    printf("Level %d: number of threads in the team: %d\n", level, omp_get_num_threads());
    
}


int main()
{
    omp_set_dynamic(0);
    #pragma omp parallel num_threads(2) 
    {
        report_num_threads(1);
        #pragma omp parallel num_threads(2) 
        {
            report_num_threads(2);
            #pragma omp parallel num_threads(2) 
            {
                report_num_threads(3);
            }
        }
    }

    return(0);
}