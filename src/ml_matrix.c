//
// Created by peixinho on 19/12/16.
//

#include <ml_matrix.h>
#include <cblas.h>
#include <ml_memory.h>

MlMatrix* ml_create_matrix(size_t nrow, size_t ncol) {
    MlMatrix* m = NULL;
    m = ml_alloc(MlMatrix);
    m->nrows = nrow;
    m->ncols = ncol;
    m->n = nrow*ncol;
    m->data = ml_alloc_array(m->n, float);
    return m;
}

void mlMultMatrixIp(MlMatrix* A, MlMatrix* B, MlMatrix* M) {
    double alpha = 1.0, beta = 0.0;

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, A->nrows, B->ncols, \
        A->ncols, alpha, A->data, A->ncols, B->data, B->ncols, beta, \
        M->data, B->ncols);
}

MlMatrix* mlMultMatrix(MlMatrix* A, MlMatrix* B) {
    MlMatrix* M = ml_create_matrix(B->ncols, A->nrows);
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
    MlMatrix* sum = ml_create_matrix(1, m->ncols);

    for (int i = 0; i < m->nrows; ++i) {
        for (int j = 0; j < m->ncols; ++j) {
            ml_mat_elem(sum, 0, j) += ml_mat_elem(m, i, j);
        }
    }

    return sum;
}

void ml_set_matrix(MlMatrix *m, float val) {
    for (int i = 0; i < m->n; ++i)
        m->data[i] = val;
}

void ml_free_matrix(MlMatrix *m) {
    ml_free(m->data);
    ml_free(m);
}

void ml_print_matrix(MlMatrix *m) {
    printf("[");
    for (int r = 0; r < m->nrows; ++r) {
        printf("[");
        for (int c = 0; c < m->ncols; ++c) {
            printf("%4.2f", ml_mat_elem(m, r, c));
            if(c < m->ncols-1)
                printf(", ");
        }
        printf("]");
        if(r<m->nrows-1)
            printf("\n");
    }
    printf("]\n");
}
