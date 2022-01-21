
#include <stdio.h>
#include <omp.h>


/*
    gcc -fopenmp doacross2.c -o doacross2
    ./doacross2

*/


#define N 5

int fn(int a, int b)
{
    return a+b;
}

void main(){
    int r,c;
    int x[N][N];
    for(c=0;c<N;c++) x[0][c]=0;

    #pragma omp parallel
    {
        #pragma omp	for ordered(2) collapse(2)	
        for(r=1;r<N;r++){	
            for(c=1;c<N;c++){	
                #pragma omp ordered depend(sink:r-1,c) depend(sink:r,c-1)       	//  wait
                x[r][c]	+= fn(x[r-1][c],	x[r][c-1]);	
                printf("id=%d, (%d,%d)<-[(%d,%d),(%d,%d)]\n",omp_get_thread_num(), r,c,r-1,c,r,c-1);
                fflush(stdout);
                #pragma omp ordered depend(source)	                            		// post
            }				
        }
    }
}
