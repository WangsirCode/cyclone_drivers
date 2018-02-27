#ifndef FFT_F
#define FFT_F FFT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//mac下M_PI在math.h中有宏定义，所以这里我们选择行的宏定义
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
