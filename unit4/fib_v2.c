
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fib ( int n ) { 
    int x,y; 
    if ( n < 2 ) return n; 

    #pragma omp task shared(x) if(n>30)
    x = fib(n-1); 

    #pragma omp task shared(y) if(n>30)
    y = fib(n-2); 

    #pragma omp taskwait 

    return x+y ;
}


// export OMP_NUM_THREADS=8

void main(int argc, char **argv)
{
  int n =50;
  if(argc == 2){
    n = atoi(argv[1]);
  }


  #pragma omp parallel
  {

      #pragma omp single
      printf("fib = %d (#threads = %d)\n", fib(n), omp_get_num_threads());
  }
}
