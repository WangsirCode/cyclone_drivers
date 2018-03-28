#ifndef FFT_H
#define FFT_H FFT_H_H

#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include <math.h>  

#ifndef M_PI  
#define M_PI 3.14159265358979323846  
#endif  

struct Complex_{  
    float real;
    float imagin;
};  
typedef struct Complex_ Complex;  
void FFT(float * src,Complex * dst,int size_n);
#endif
