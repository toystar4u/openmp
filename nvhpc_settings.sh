
NVARCH=`uname -s`_`uname -m`; export NVARCH
NVCOMPILERS=/opt/nvidia/hpc_sdk; export NVCOMPILERS
MANPATH=$MANPATH:$NVCOMPILERS/$NVARCH/21.1/compilers/man; export MANPATH
PATH=$NVCOMPILERS/$NVARCH/21.1/compilers/bin:$PATH; export PATH

export PATH=$NVCOMPILERS/$NVARCH/21.1/comm_libs/mpi/bin:$PATH
export MANPATH=$MANPATH:$NVCOMPILERS/$NVARCH/21.1/comm_libs/mpi/man