//
// Created by peixinho on 20/12/16.
//

#ifndef ML_ML_DATASET_H
#define ML_ML_DATASET_H

#include <ml_matrix.h>

typedef enum {TRAIN = 1, TEST = 2, ALL = 3} ml_SampleStatus;

typedef struct {

    int nsamples;
    int nfeats;
    int nclasses;

    ml_SampleStatus* status;

    MlMatrix* feats;
    MlMatrix* predict;
    MlMatrix* label;
    MlMatrix* sample_weight;
    MlMatrix* predict_weight;

} ml_DataSet;

void ml_print_stats_dataset(ml_DataSet *dataset);
ml_DataSet* ml_load_csv_dataset(const char *filename, int classPos);
ml_DataSet* ml_create_dataSet(int nsamples, int nfeats, int nclasses);
ml_DataSet* ml_select_dataset(ml_DataSet *dataset, ml_SampleStatus status);
void ml_select_train_samples(ml_DataSet *dataset, float trainPerc);

#endif //ML_ML_DATASET_H
