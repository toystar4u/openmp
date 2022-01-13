#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zero-upper")         //Enable AVX
//#pragma GCC target("avx")  //Enable AVX
#pragma GCC target("sse")  //Enable AVX


#include <x86intrin.h> //AVX/SSE Extensions
#include <omp.h>

/*
    gcc -O3  -fopenmp -fopt-info-vec-optimized pi_omp_vec.c -o pi_omp_vec

*/

#define NTHREADS    4


float pi_vec(int num_steps)
{ 
    float scalar_one =1.0, scalar_zero = 0.0, ival, scalar_four =4.0, step, pi, vsum[4];
    float local_sum[NTHREADS]; // set NTHREADS elsewhere, often to num of cores
    step = 1.0/(float) num_steps;

    #pragma omp parallel 
    { 
        int ID = omp_get_thread_num();

        __m128 ramp = _mm_setr_ps(0.5, 1.5, 2.5, 3.5);
        __m128 one = _mm_load1_ps(&scalar_one);
        __m128 four = _mm_load1_ps(&scalar_four);
        __m128 vstep = _mm_load1_ps(&step);
        __m128 sum = _mm_load1_ps(&scalar_zero);
        __m128 xvec; __m128 denom; __m128 eye;
        
        #pragma omp for
        for (int i=0;i< num_steps; i=i+4){ // unroll loop 4 times
            ival = (float)i; // and assume num_steps%4 = 0
            eye = _mm_load1_ps(&ival);
            xvec = _mm_mul_ps(_mm_add_ps(eye,ramp),vstep);
            denom = _mm_add_ps(_mm_mul_ps(xvec,xvec),one);
            sum = _mm_add_ps(_mm_div_ps(four,denom),sum);
        }
        _mm_store_ps(&vsum[0],sum);

        local_sum[ID] = step * (vsum[0]+vsum[1]+vsum[2]+vsum[3]); 
    }
    
    for(int k = 0; k<NTHREADS;k++) pi+=local_sum[k]; 

    return pi;
}

void main()
{
    long num_steps = 10000000000000; 
 
    float pi;

    omp_set_num_threads(NTHREADS);
    pi  = pi_vec(num_steps);

}