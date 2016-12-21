//
// Created by peixinho on 20/12/16.
//

#ifndef ML_ML_DATASET_H
#define ML_ML_DATASET_H

#include <ml_matrix.h>

typedef enum {TRAIN, TEST} MlSampleStatus;

typedef struct {

    int nsamples;
    int nfeats;
    int nclasses;

    MlSampleStatus* status;

    MlMatrix* X;
    MlMatrix* Y;
    MlMatrix* weight;
    MlMatrix* prob;

} MlDataSet;

MlDataSet* mlLoadCsvDataSet(const char *filename, int classPos);
MlDataSet* mlCreateDataSet(int nsamples, int nfeats, int nclasses);

#endif //ML_ML_DATASET_H
