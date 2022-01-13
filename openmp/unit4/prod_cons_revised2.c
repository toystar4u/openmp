#include<stdio.h>
#include<stdlib.h>

#include<omp.h>

/*
    $ gcc -fopenmp prod_cons_revised2.c -o prod_cons_revised2
    $ export OMP_NUM_THREADS=4
    $ ./prod_cons_revised2
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
            #pragma omp write seq_cst
            flag = 1; 
        }

        // consumer
        #pragma omp section 
        { 
            while (1){ 
                #pragma omp atomic read seq_cst
                flag_tmp = flag;
                if(flag_tmp==1) break;
            } 

            sum = sum_array(N, A); 
        } 
    }

    runtime = omp_get_wtime() - runtime; 
    printf(" In %lf secs, The sum is %lf \n",runtime,sum); 

    return 0;
}
