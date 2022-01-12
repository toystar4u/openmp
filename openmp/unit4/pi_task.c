#include <stdio.h>
#include <omp.h>

/*
    $ gcc -fopenmp pi_task.c -o pi_task
    $ export OMP_NUM_THREADS=4
    $ ./pi_task
*/

static long num_steps = 1024*1024;
#define MIN_BLK 1024

double cal_pi(int Nstart,int Nfinish,double step)
{ 
    int i,iblk;
    double x, sum = 0.0,sum1, sum2;
    
    if (Nfinish-Nstart < MIN_BLK){
        for (i=Nstart;i< Nfinish; i++){
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
    }else{
        iblk = Nfinish-Nstart;
        
        #pragma omp task shared(sum1)
        sum1 = cal_pi(Nstart, Nfinish-iblk/2,step);
        
        #pragma omp task shared(sum2)
        sum2 = cal_pi(Nfinish-iblk/2, Nfinish, step);
        
        #pragma omp taskwait
        sum = sum1 + sum2;
    }
    
    return sum;
}


int main ()
{
    int i;
    double step, pi, sum;
    step = 1.0/(double) num_steps;
    
    #pragma omp parallel
    {
        #pragma omp single
        sum =   cal_pi(0,num_steps,step);
    }

    pi = step * sum;

    return 0;
}