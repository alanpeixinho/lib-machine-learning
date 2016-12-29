//
// Created by peixinho on 20/12/16.
//

#ifndef ML_ML_DATASET_H
#define ML_ML_DATASET_H

#include <ml_matrix.h>

typedef enum {TRAIN = 1, TEST = 2, ALL = 3} MlSampleStatus;

typedef struct {

    int nsamples;
    int nfeats;
    int nclasses;

    MlSampleStatus* status;

    MlMatrix* feats;
    MlMatrix* predict;
    MlMatrix* label;
    MlMatrix* sampleWeight;
    MlMatrix* predictWeight;

} MlDataSet;

void mlPrintStatsDataSet(MlDataSet* dataset);
MlDataSet* mlLoadCsvDataSet(const char *filename, int classPos);
MlDataSet* mlCreateDataSet(int nsamples, int nfeats, int nclasses);
MlDataSet* mlSelectDataSet(MlDataSet* dataset, MlSampleStatus status);
void mlSelectTrainSamples(MlDataSet* dataset, float trainPerc);

#endif //ML_ML_DATASET_H
