//
// Created by Peixinho on 28/12/16.
//

#ifndef ML_ML_KNN_H_H
#define ML_ML_KNN_H_H

#include <stdbool.h>
#include "ml_dataset.h"

typedef struct {

    int k;
    MlDataSet* train;
    MlMatrix* _dist;
    MlMatrix* _voting;
    int* _kNearest;
    bool* _selected;

} MlKNN;

MlKNN* mlCreateKNN(int k);
float mlPredictKNN(MlKNN* knn, float X[]);
void mlTrainKNN(MlKNN* knn, MlDataSet* dataset);

#endif //ML_ML_KNN_H_H
