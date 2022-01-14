#include <stdio.h>
#include <math.h>


/*

    gcc -o jacobi_serial jacobi_serial.c -lm

*/


#define TOL         (1e-6)
#define MAX_ITERS   100

#define TYPE        float


int main()
{
    const int Ndim=3;

    int i, j, iters=0;
    double conv,tmp;

    TYPE *xnew, *xold;

    // test code for Ndim=3
    TYPE A[]   ={  (TYPE)4,(TYPE)-1,(TYPE)-1,
                            (TYPE)-2, (TYPE)6, (TYPE)1,
                            (TYPE)-1, (TYPE)1, (TYPE)7
                            };

    TYPE b[]        ={(TYPE)3, (TYPE)9, (TYPE)6};

    TYPE x1[Ndim], x2[Ndim];
    
    // initialize the matrix A and vectors x1, x2, anb b
    // init(A,b,Ndim);
    for(i=0;i<Ndim;i++){
        x1[i] = (TYPE)0;
        x2[i] = (TYPE)0;
    }

    while((conv > TOL) && (iters<MAX_ITERS)){
        iters++;
        xnew = iters % 2 ? x2 : x1;
        xold = iters % 2 ? x1 : x2;
        
        for (i=0; i<Ndim; i++){
            xnew[i] = (TYPE) 0.0;
            for (j=0; j<Ndim;j++){
                if(i!=j)
                    xnew[i]+= A[i*Ndim + j]*xold[j];   // (L+U)x
            }
            xnew[i] = (b[i]-xnew[i])/A[i*Ndim+i];       // b-(L+U)x)/D
        }

        // test convergence
        conv = 0.0;
        for (i=0; i<Ndim; i++){
            tmp = xnew[i]-xold[i];
            conv += tmp*tmp;
        }
    
        conv = sqrt((double)conv);                  // ||x-xo||_2
    } // end while loop

    return 0;
}