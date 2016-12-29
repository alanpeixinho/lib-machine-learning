//
// Created by peixinho on 19/12/16.
//

#include <ml_matrix.h>
#include <cblas.h>
#include <ml_memory.h>

MlMatrix* mlCreateMatrix(size_t nrow, size_t ncol) {
    MlMatrix* m = NULL;
    m = mlAlloc(MlMatrix);
    m->nrows = nrow;
    m->ncols = ncol;
    m->n = nrow*ncol;
    m->data = mlAllocArray(m->n, float);
    return m;
}

void mlMultMatrixIp(MlMatrix* A, MlMatrix* B, MlMatrix* M) {
    double alpha = 1.0, beta = 0.0;

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, A->nrows, B->ncols, \
        A->ncols, alpha, A->data, A->ncols, B->data, B->ncols, beta, \
        M->data, B->ncols);
}

MlMatrix* mlMultMatrix(MlMatrix* A, MlMatrix* B) {
    MlMatrix* M = mlCreateMatrix(B->ncols, A->nrows);
    mlMultMatrixIp(A, B, M);
    return M;
}

float mlMeanMatrix(MlMatrix* m) {
    float mean = 0.0f;
    for (int i = 0; i < m->n; ++i) {
        mean += m->data[i] / m->n;
    }
    return mean;
}

MlMatrix* mlMatrixSumCol(MlMatrix* m) {
    MlMatrix* sum = mlCreateMatrix(1, m->ncols);

    for (int i = 0; i < m->nrows; ++i) {
        for (int j = 0; j < m->ncols; ++j) {
            mlMatElem(sum, 0, j) += mlMatElem(m, i, j);
        }
    }

    return sum;
}

void mlSetMatrix(MlMatrix* m, float val) {
    for (int i = 0; i < m->n; ++i)
        m->data[i] = val;
}

void mlFreeMatrix(MlMatrix* m) {
    mlFree(m->data);
    mlFree(m);
}

void mlPrintMatrix(MlMatrix* m) {
    printf("[");
    for (int r = 0; r < m->nrows; ++r) {
        printf("[");
        for (int c = 0; c < m->ncols; ++c) {
            printf("%4.2f", mlMatElem(m, r, c));
            if(c < m->ncols-1)
                printf(", ");
        }
        printf("]");
        if(r<m->nrows-1)
            printf("\n");
    }
    printf("]\n");
}
