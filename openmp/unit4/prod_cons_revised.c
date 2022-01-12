#include<stdio.h>
#include<stdlib.h>

#include<omp.h>

/*
    $ gcc -fopenmp prod_cons_revised.c -o prod_cons_revised
    $ export OMP_NUM_THREADS=4
    $ ./prod_cons_revised
*/



int N=1000000000;


void fill_rand(int N, double *buf)
{
    for(int i=0;i<N;i++)
        buf[i] = 1;
}


double sum_array(int N, double *buf)
{
    double sum =0;
    for(int i=0;i<N;i++)
      sum += buf[i];      
}


int main() { 
    double *A, sum, runtime;  
    int flag = 0, flag_tmp; 
    
    A = (double *)malloc(N*sizeof(double)); 
    runtime = omp_get_wtime(); 
    
    
    #pragma omp parallel sections 
    {

        // prouducer
        #pragma omp section 
        {
            fill_rand(N, A); 		
            #pragma omp flush
            #pragma omp write
            flag = 1; 
            #pragma omp flush (flag) 
        }

        // consumer
        #pragma omp section 
        { 
            while (1){ 
                #pragma omp flush (flag) 
                #pragma omp atomic read
                flag_tmp = flag;
                if(flag_tmp==1) break;
            } 

            #pragma omp flush 
            sum = sum_array(N, A); 
        } 
    }

    runtime = omp_get_wtime() - runtime; 
    printf(" In %lf secs, The sum is %lf \n",runtime,sum); 

    return 0;
}
