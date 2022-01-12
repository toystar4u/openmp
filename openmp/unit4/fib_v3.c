
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int serfib(int n){
	static int fibtable[31]={
    0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 
    987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 
    121393, 196418, 317811, 514229, 832040
  };


	return fibtable[n];
}


int fib ( int n ) { 
    int x,y; 
    if ( n < 2 ) return n; 
    if ( n <= 30) return serfib(n);


    #pragma omp task shared(x)
    x = fib(n-1); 

    #pragma omp task shared(y)
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
