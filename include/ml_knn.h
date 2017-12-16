//
// Created by Peixinho on 28/12/16.
//

#ifndef ML_ML_KNN_H_H
#define ML_ML_KNN_H_H

#include <stdbool.h>
#include "ml_dataset.h"

typedef struct {

    int k;
    ml_DataSet* train;
    MlMatrix* _dist;
    MlMatrix* _voting;
    int* _k_nearest;
    bool* _selected;

} ml_KNN;

ml_KNN* ml_create_knn(int k);
float ml_predict_knn(ml_KNN *knn, float *X);
void ml_train_knn(ml_KNN *knn, ml_DataSet *dataset);

#endif //ML_ML_KNN_H_H
