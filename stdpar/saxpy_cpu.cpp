
#include <cmath>

void saxpy_cpu(int n, float a, float *x, float *y)
{
	for (int i = 0; i < n; ++i)
		y[i] = a * x[i] + y[i];
}




int main(){
    // Perform SAXPY on ~33M elements
    float alpha = 2.0;
    
    long n = 1UL << 30;
    
    float *x = new float[n];
    float *y = new float[n];

    for(long i=0;i<n;i++){
        x[i] = 1.f;
        y[i] = 1.f;
    }
    
    saxpy_cpu(n, alpha, x, y);

    delete[] x;
    delete[] y;

    return 0;
}