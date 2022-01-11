#include<stdio.h>

/*
    gcc pi_single.c -o pi_single

*/


static long num_steps = 100000000; 
double step; 

int main () {
    long i; double x, pi, sum = 0.0; 

    step = 1.0/(double) num_steps;        	// 𝚫x

    for (i=0;i< num_steps; i++){ 
        x = (i+0.5)*step;                   // xi
        sum = sum + 4.0/(1.0+x*x); 	        // F(xi)= 4.0/(1.0+xi2); sum = ΣF(xi) 
    } 
    pi = step * sum;                        // pi = 𝚫x*ΣF(xi) 

    return 0;
} 
