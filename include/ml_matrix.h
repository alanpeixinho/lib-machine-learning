//
// Created by peixinho on 19/12/16.
//

#ifndef ML_ML_MATRIX_H
#define ML_ML_MATRIX_H

#include <ml.h>

#define mlMatElem(m, r, c) ((m)->data[r * m->ncols + c])
#define mlMatRow(m, r) ((m)->data + (r * m->ncols))

typedef struct {
    float *data;
    size_t n;
    size_t nrows;
    size_t ncols;
} MlMatrix;

MlMatrix* mlCreateMatrix(size_t nrow, size_t ncol);
MlMatrix* mlMultMatrix(MlMatrix* m1, MlMatrix* m2);
float mlMeanMatrix(MlMatrix* m);
MlMatrix* mlMatrixSumCol(MlMatrix* m);
void mlSetMatrix(MlMatrix* m, float val);
void mlFreeMatrix(MlMatrix* m);
void mlPrintMatrix(MlMatrix* m);

#endif //ML_ML_MATRIX_H
