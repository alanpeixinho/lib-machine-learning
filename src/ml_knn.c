//
// Created by Peixinho on 28/12/16.
//

#include <float.h>
#include <ml_memory.h>
#include <ml_knn.h>
#include <ml_math.h>
#include <ml_matrix.h>
#include <ml_dataset.h>

ml_KNN* ml_create_knn(int k) {
    ml_KNN* knn = ml_alloc(ml_KNN);
    knn->k = k;
    knn->_k_nearest = ml_alloc_array(k, int);
    return knn;
}

void ml_train_knn(ml_KNN *knn, ml_DataSet *dataset) {

	ml_print_stats_dataset(dataset);
    knn->train = ml_select_dataset(dataset, TRAIN);

	ml_print_stats_dataset(knn->train);
    knn->_voting = ml_create_matrix(dataset->nclasses, 1);

    knn->_dist = ml_create_matrix(knn->train->nsamples, 1);
    knn->_selected = ml_alloc_array(knn->train->nsamples, bool);
}

void ml_print_array(float *val, int n) {
    for(int i=0 ; i<n; ++i)
        printf("%f ", val[i]);
    printf("\n");
}

float ml_predict_knn(ml_KNN *knn, float *X) {

    for (int i = 0; i < knn->train->nsamples; ++i) {
        ml_mat_elem(knn->_dist, i, 0) = ml_norm_l2(ml_mat_row(knn->train->feats, i), X, knn->train->nfeats);
        knn->_selected[i] = false;
    }

    ml_set_matrix(knn->_voting, 0);

    for(int k = 0; k<knn->k; ++k) {
        float min = FLT_MAX;
        int selected;

        for (int i = 0; i < knn->train->nsamples; ++i) {
            if(ml_mat_elem(knn->_dist, i, 0) < min && !(knn->_selected[i])) {
                min = ml_mat_elem(knn->_dist, i, 0);
                selected = i;
            }
        }

        int label = (int) ml_mat_elem(knn->train->label, selected, 0);
        ml_mat_elem(knn->_voting, label, 0)++;
        knn->_selected[selected] = true;
    }

    return ml_arg_max_float(knn->_voting->data, knn->train->nclasses);
}