

#define BLK_SIZE    1024


__global__ void saxpy_cuda(int n, float a, float *x, float *y){
     int t_id = threadIdx.x + blockDim.x * blockIdx.x;
     int stride = blockDim.x * gridDim.x;
     for (int i = t_id; i < n; i += stride)
     {
          y[i] = a * x[i] + y[i];
     }
}

int main()
{
     long n = 1UL << 30;
     float *x, *y, alpha=2.0;
     float *dx, *dy;

     x = new float[n];
     y = new float[n];

     cudaMalloc(&dx, n * sizeof(float));
     cudaMalloc(&dy, n * sizeof(float));

     for(long i=0;i<n;i++){
          x[i] = 1.f;
          y[i] = 1.f;
     }

     cudaMemcpy(dx, x, n*sizeof(float), cudaMemcpyHostToDevice);
     cudaMemcpy(dy, y, n*sizeof(float), cudaMemcpyHostToDevice);

     // 2^(10*5)
     saxpy_cuda<<<(n+BLK_SIZE-1)/BLK_SIZE, BLK_SIZE>>>(n, alpha, dx, dy);
     cudaDeviceSynchronize();

     cudaMemcpy(y, dy, n*sizeof(float), cudaMemcpyDeviceToHost);

     cudaFree(dx);
     cudaFree(dy);


     delete[] x;
     delete[] y;

     return 0;
}