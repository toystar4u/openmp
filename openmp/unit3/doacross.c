
#include <stdio.h>
#include <omp.h>


/*
    gcc -fopenmp doacross.c -o doacross
    ./doacross

*/


#define N 12

int fn(int a, int b)
{
    return a+b;
}

void main(){
    int a[N],b[N],c[N],d[N],e[N];

    for(int j=0;j<0;j++){
        b[j]=j;
        c[j]=3;
        d[j]=j*5;
        e[j]=j;
    }
    
    a[1]=a[0]=0;
    #pragma omp parallel
    {
        #pragma omp	for ordered(1)
        for (int i =2; i < N; i++) {

            #pragma omp ordered depend(sink:i-2)
            a[i] = a[i-2] + b[i]*c[i] + d[i]/(e[i]+1) + 1;

            printf("id=%d, a[%d] <- a[%d]\n",omp_get_thread_num(),i,i-2);

            #pragma omp	ordered depend(source)	
        }

    }
}
