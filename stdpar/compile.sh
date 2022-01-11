nvcc -O3 -o saxpy_cuda saxpy_cuda.cu
g++ -O3 -o saxpy_cpu saxpy_cpu.cpp

# apt install libtbb-dev
g++ -O3 saxpy_stdpar.cpp -o saxpy_stdpar_gpp -std=c++17 -ltbb -pthread


# NVHPC
nvc++ -O3 saxpy_stdpar.cpp -o saxpy_stdpar_nvpp -std=c++17 -stdpar

echo ""
echo "single CPU"
time ./saxpy_cpu

echo ""
echo "CUDA"
time ./saxpy_cuda

echo ""
echo "stdpar (GCC)"
time ./saxpy_stdpar_gpp

echo ""
echo "NVPP stdpar (NVC)"
time ./saxpy_stdpar_nvpp