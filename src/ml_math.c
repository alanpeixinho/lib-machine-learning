//
// Created by Peixinho on 28/12/16.
//

#include <math.h>
#include <float.h>
#include <stdlib.h>

float mlFastPow(float x, int p) {
    switch (p) {
        case 2:
            return x*x;
        case 3:
            return x*x*x;
        case 4:
            return mlFastPow(x*x, 2);
        default:
            return pow(x, p);
    }
}

int mlArgMax(float* val, int n) {
    float max = -FLT_MAX;
    int idx;
    for (int i = 0; i < n; ++i) {
        if(val[i] > max){
            idx = i;
            max = val[i];
        }
    }
    return idx;
}


float mlRand() {
    return ((float)rand()/(float)(RAND_MAX));
}

float mlUniformRand(float min, float max) {
    return min + mlRand()*(max-min);
}