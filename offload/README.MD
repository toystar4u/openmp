
# OpenMP GPU  offload



### single
```
$ ./saxpy2
Time of kernel: 3.464837
Time of kernel: 1.865655
Time of kernel: 1.863598
Time of kernel: 1.862695
Time of kernel: 1.864771
Time of kernel: 1.867418
Time of kernel: 1.866538
Time of kernel: 1.863777
Time of kernel: 1.861561
Time of kernel: 1.863837

```



## GCC 

### installation

```
# for NVIDIA GPUs
sudo apt install gcc-offload-nvptx    

# for AMD GPUs
sudo apt install gcc-offload-amdgcn
```


### build
- version : 9.3.0
```
gcc -fopenmp -foffload=nvptx-none -fcf-protection=none -foffload=-misa=sm_35 -fno-stack-protector saxpy.c -o saxpy
```

### run
```
$./saxpy2_gpu
Time of kernel: 3.402076
Time of kernel: 1.474261
Time of kernel: 1.475354
Time of kernel: 1.473663
Time of kernel: 1.475119
Time of kernel: 1.475000
Time of kernel: 1.475195
Time of kernel: 1.475161
Time of kernel: 1.474766
Time of kernel: 1.475629

```


## NVIDIA HPC 

### installation for CUDA 11.2
- download and install
```
$ wget https://developer.download.nvidia.com/hpc-sdk/21.1/nvhpc-21-1_21.1_amd64.deb \
       https://developer.download.nvidia.com/hpc-sdk/21.1/nvhpc-2021_21.1_amd64.deb
$ apt-get install ./nvhpc-21-1_21.1_amd64.deb ./nvhpc-2021_21.1_amd64.deb
```

- environment setup
```
$ NVARCH=`uname -s`_`uname -m`; export NVARCH
$ NVCOMPILERS=/opt/nvidia/hpc_sdk; export NVCOMPILERS
$ MANPATH=$MANPATH:$NVCOMPILERS/$NVARCH/21.1/compilers/man; export MANPATH
$ PATH=$NVCOMPILERS/$NVARCH/21.1/compilers/bin:$PATH; export PATH

$ export PATH=$NVCOMPILERS/$NVARCH/21.1/comm_libs/mpi/bin:$PATH
$ export MANPATH=$MANPATH:$NVCOMPILERS/$NVARCH/21.1/comm_libs/mpi/man
```

### build
```
nvc++ -mp=gpu -gpu=cc80  saxpy2.c -o saxpy2_nv
```

### run
```
$ ./saxpy2_nv
Time of kernel: 3.002666
Time of kernel: 1.409490
Time of kernel: 1.385120
Time of kernel: 1.374664
Time of kernel: 1.388184
Time of kernel: 1.379841
Time of kernel: 1.374224
Time of kernel: 1.372691
Time of kernel: 1.410059
Time of kernel: 1.397759
```
