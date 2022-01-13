
#include <stdio.h>
#include <omp.h>

/*
    gcc -fopenmp check_device.c -o check_device
*/


int main() { 
    
    printf("There are %d devices\n", omp_get_num_devices()); 

    return 0;
} 
