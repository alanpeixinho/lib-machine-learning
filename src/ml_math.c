//
// Created by Peixinho on 28/12/16.
//

#include <math.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>

float ml_fast_pow(float x, int p) {
    switch (p) {
        case 2:
            return x*x;
        case 3:
            return x*x*x;
        case 4:
            return ml_fast_pow(x * x, 2);
        default:
            return pow(x, p);
    }
}

int ml_arg_max_float(float *val, int n) {
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

int ml_arg_max_int(int *val, int n) {
	int max = -INT_MAX;
	int idx;
	for (int i = 0; i < n; ++i) {
		if(val[i] > max){
			idx = i;
			max = val[i];
		}
	}
	return idx;
}


float ml_rand() {
    return ((float)rand()/(float)(RAND_MAX));
}

float ml_uniform_rand(float min, float max) {
    return min + ml_rand()*(max-min);
}