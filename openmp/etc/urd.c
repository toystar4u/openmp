
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>



#define N 128

int main()
{
    int *a;
    int result = INT_MAX;
    
    // create and initialize the array a
    a = (int*)malloc(sizeof(int)*N);
    for(int i=0;i<N;i++) a[i]=N-i;

    // declare the user defined reduction
    #pragma omp declare reduction (my_abs_min : int : \
            omp_out = abs(omp_in) < omp_out ? abs(omp_in) : abs (omp_out)) \
            initializer (omp_priv = INT_MAX)
    #pragma omp parallel for reduction(my_abs_min:result)
    for (int i=0; i<N; i++){
        if (abs(a[i]) < result)
            result = abs(a[i]);         
    }

    printf("result = %d \n",result);

    free(a);
}


