#include <stdio.h>
#include <omp.h>

#define SZ 1000000

void saxpy() {
	float a, x[SZ], y[SZ];

	double t = 0.0;
	double tb, te;
	tb = omp_get_wtime();
	
	#pragma omp target map(to:x[0:SZ]) map(tofrom:y[0:SZ])
	#pragma omp parallel for simd
	for (int i = 0; i < SZ; i++) {
		y[i] = a * x[i] + y[i];
	}
	te = omp_get_wtime();
	t = te - tb;
	printf("Time of kernel: %lf\n", t);
}


void main()
{

	saxpy();
}

