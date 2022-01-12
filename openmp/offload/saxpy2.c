#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

const long SZ = 1000000000;

void saxpy(float *x, float *y) {
	float a;

	double t = 0.0;
	double tb, te;
	tb = omp_get_wtime();
	
    // method 1
	//#pragma omp target map(to:x[0:SZ]) map(tofrom:y[0:SZ])
	//#pragma omp parallel for smid
    
    // method 2
	#pragma omp target data map(to:x[0:SZ]) map(tofrom:y[0:SZ])
    #pragma omp target teams distribute parallel for
	for (long i = 0; i < SZ; i++) {
		y[i] = a * x[i] + y[i];
	}
	te = omp_get_wtime();
	t = te - tb;
	printf("Time of kernel: %lf\n", t);
}


void main()
{
    float *x = (float*) malloc(SZ*sizeof(float));
    float *y = (float*) malloc(SZ*sizeof(float));

    for(int i=0;i<10;i++)
	    saxpy(x,y);

    free(x);
    free(y);
}

