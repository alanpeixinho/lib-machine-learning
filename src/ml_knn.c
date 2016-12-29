//
// Created by Peixinho on 28/12/16.
//

#include <float.h>
#include <ml_memory.h>
#include <ml_knn.h>
#include <ml_math.h>
#include <ml_matrix.h>
#include <ml_dataset.h>

double mlNormL2(float x[], float y[], int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; ++i) {
        sum += mlFastPow(x[i] - y[i], 2);
//        printf("%f %f\n", x[i], y[i]);
    }
    return sqrtf(sum);
}

MlKNN* mlCreateKNN(int k) {
    MlKNN* knn = mlAlloc(MlKNN);
    knn->k = k;
    knn->_kNearest = mlAllocArray(k, int);
    return knn;
}

void mlTrainKNN(MlKNN* knn, MlDataSet* dataset) {

    mlPrintStatsDataSet(dataset);
    knn->train = mlSelectDataSet(dataset, TRAIN);

    mlPrintStatsDataSet(knn->train);
    knn->_voting = mlCreateMatrix(dataset->nclasses, 1);

    knn->_dist = mlCreateMatrix(knn->train->nsamples, 1);
    knn->_selected = mlAllocArray(knn->train->nsamples, bool);
}

void mlPrintArray(float val[], int n) {
    for(int i=0 ; i<n; ++i)
        printf("%f ", val[i]);
    printf("\n");
}

float mlPredictKNN(MlKNN* knn, float X[]) {

    for (int i = 0; i < knn->train->nsamples; ++i) {
        mlMatElem(knn->_dist, i, 0) = mlNormL2(mlMatRow(knn->train->feats, i), X, knn->train->nfeats);
        knn->_selected[i] = false;
    }

//    mlPrintMatrix(knn->_dist);

    mlSetMatrix(knn->_voting, 0);

    for(int k = 0; k<knn->k; ++k) {
        float min = FLT_MAX;
        int selected;

        for (int i = 0; i < knn->train->nsamples; ++i) {
            if(mlMatElem(knn->_dist, i, 0) < min && !(knn->_selected[i])) {
                min = mlMatElem(knn->_dist, i, 0);
                selected = i;
            }
        }

        int label = (int) mlMatElem(knn->train->label, selected, 0);
        mlMatElem(knn->_voting, label, 0)++;
        knn->_selected[selected] = true;
    }

    return mlArgMax(knn->_voting->data, knn->train->nclasses);
}