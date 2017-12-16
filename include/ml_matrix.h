//
// Created by peixinho on 19/12/16.
//

#ifndef ML_ML_MATRIX_H
#define ML_ML_MATRIX_H

#include <ml.h>

#define ml_mat_elem(m, r, c) ((m)->data[r * m->ncols + c])
#define ml_mat_row(m, r) ((m)->data + (r * m->ncols))

typedef struct {
    float *data;
    size_t n;
    size_t nrows;
    size_t ncols;
} MlMatrix;

MlMatrix* ml_create_matrix(size_t nrow, size_t ncol);
MlMatrix* mlMultMatrix(MlMatrix* m1, MlMatrix* m2);
float mlMeanMatrix(MlMatrix* m);
MlMatrix* mlMatrixSumCol(MlMatrix* m);
void ml_set_matrix(MlMatrix *m, float val);
void ml_free_matrix(MlMatrix *m);
void ml_print_matrix(MlMatrix *m);

#endif //ML_ML_MATRIX_H
