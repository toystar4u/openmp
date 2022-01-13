#include<stdio.h>
#include<omp.h>

/*
    gcc -O3 -fopenmp pi_omp_simd.c -o pi_omp_simd

*/


static long num_steps = 10000000000000; 
float step; 

int main () {
    long i; float x, pi, sum = 0.0f; 

    step = 1.0/(float) num_steps;        	// 𝚫x
    
    #pragma omp parallel for simd reduction(+:sum) 
     for (i=0;i< num_steps; i++){ 
        x = (i+0.5f)*step;                   // xi
        sum = sum + 4.0f/(1.0f+x*x); 	        // F(xi)= 4.0/(1.0+xi2); sum = ΣF(xi) 
    } 
    pi = step * sum;                        // pi = 𝚫x*ΣF(xi) 

    return 0;
} 
