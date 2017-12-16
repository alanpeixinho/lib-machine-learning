//
// Created by Peixinho on 29/12/16.
//

#include <ml_dataset.h>
#include <ml_matrix.h>

float ml_accuracy(ml_DataSet* dataset) {
    int nsamples = 0;
    int ncorrects = 0;
    for (int i = 0; i < dataset->nsamples; ++i) {
        if(dataset->status[i] & TEST) {
            nsamples++;
            if(ml_mat_elem(dataset->predict, i, 0) == ml_mat_elem(dataset->label, i, 0)) {
                ncorrects++;
            }
        }
    }
    return (float)ncorrects/(float)nsamples;
}

float ml_norm_l2(float x[], float y[], int n) {
	float sum = 0.0f;
	for (int i = 0; i < n; ++i) {
		sum += ml_fast_pow(x[i] - y[i], 2);
	}
	return sqrtf(sum);
}