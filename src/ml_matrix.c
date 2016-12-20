//
// Created by peixinho on 19/12/16.
//

#include <ml_matrix.h>
#include <cblas.h>
#include <ml_memory.h>

MlMatrix* mlCreateMatrix(size_t nrow, size_t ncol) {
    MlMatrix* m = mlAlloc(MlMatrix);
    m->nrows = nrow;
    m->ncols = ncol;
    m->n = nrow*ncol;
    m->data = mlAllocArray(m->n, float);
    return m;
}

MlMatrix* mlMultMatrix(MlMatrix* A, MlMatrix* B) {
    MlMatrix* M = mlCreateMatrix(B->ncols, A->nrows);
    mlMultMatrixIp(A, B, M);
    return M;
}

void mlMultMatrixIp(MlMatrix* A, MlMatrix* B, MlMatrix* M) {
    double alpha = 1.0, beta = 0.0;

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, A->nrows, B->ncols, \
        A->ncols, alpha, A->data, A->ncols, B->data, B->ncols, beta, \
        M->data, B->ncols);
}