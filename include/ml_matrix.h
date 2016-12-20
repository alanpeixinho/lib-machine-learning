//
// Created by peixinho on 19/12/16.
//


#ifndef ML_ML_MATRIX_H
#define ML_ML_MATRIX_H

#include <ml.h>

typedef struct {
    float *data;
    size_t n;
    size_t nrows, ncols;
} MlMatrix;

MlMatrix* mlCreateMatrix(size_t nrow, size_t ncol);
MlMatrix* mlMultMatrix(MlMatrix* m1, MlMatrix* m2);

#endif //ML_ML_MATRIX_H
