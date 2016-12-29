//
// Created by Peixinho on 29/12/16.
//

#include <ml_dataset.h>
#include <ml_matrix.h>

float ml_accuracy(MlDataSet* dataset) {
    int nsamples = 0;
    int ncorrects = 0;
    for (int i = 0; i < dataset->nsamples; ++i) {
        if(dataset->status[i] & TEST) {
            nsamples++;
            if(mlMatElem(dataset->predict, i, 0) == mlMatElem(dataset->label, i, 0)) {
                ncorrects++;
            }
        }
    }
    return (float)ncorrects/(float)nsamples;
}