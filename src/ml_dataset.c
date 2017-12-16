//
// Created by peixinho on 20/12/16.
//

#include <ml_dataset.h>
#include <ml_memory.h>
#include <ml_csv.h>
#include <ml_matrix.h>
#include <ml_dataset.h>
#include <ml_math.h>

ml_DataSet* ml_create_dataSet(int nsamples, int nfeats, int nclasses) {

    ml_DataSet* dataset = ml_alloc(ml_DataSet);
    dataset->nsamples = nsamples;
    dataset->nfeats = nfeats;
    dataset->nclasses = nclasses;

    dataset->feats = ml_create_matrix(nsamples, nfeats);
    dataset->label = ml_create_matrix(nsamples, 1);
    dataset->predict = ml_create_matrix(nsamples, 1);
    dataset->sample_weight = ml_create_matrix(nsamples, 1);
    dataset->predict_weight = ml_create_matrix(nsamples, nclasses);

    dataset->status = ml_alloc_array(nsamples, ml_SampleStatus);

    return dataset;
}

int ml_samples_number(ml_DataSet *dataset, ml_SampleStatus status) {
    int n = 0;
    for (int i = 0; i < dataset->nsamples; ++i) {
        if(dataset->status[i] & status) {
            n++;
        }
    }
    return n;
}

ml_DataSet* ml_select_dataset(ml_DataSet *dataset, ml_SampleStatus status) {
    int n = ml_samples_number(dataset, status);

    ml_DataSet* selected = ml_create_dataSet(n, dataset->nfeats, dataset->nclasses);
    ml_set_matrix(selected->feats, 42);

    int s = 0;
    for (int i = 0; i < dataset->nsamples; ++i) {
        if(dataset->status[i] & status) {
            ml_mat_elem(selected->sample_weight, s, 0) = ml_mat_elem(dataset->sample_weight, i, 0);
            ml_mat_elem(selected->label, s, 0) = ml_mat_elem(dataset->label, i, 0);
            ml_mat_elem(selected->predict, s, 0) = ml_mat_elem(dataset->predict, i, 0);

            for (int j = 0; j < dataset->nfeats; ++j) {
                ml_mat_elem(selected->feats, s, j) = ml_mat_elem(dataset->feats, i, j);
            }

            for (int c = 0; c < dataset->nclasses; ++c) {
                ml_mat_elem(selected->predict_weight, s, c) = ml_mat_elem(dataset->predict_weight, i, c);
            }
            s++;
        }
    }

    return selected;
}

void ml_print_stats_dataset(ml_DataSet *dataset) {
    printf("# Samples: %d, ", dataset->nsamples);
    printf("# Feats: %d, ", dataset->nfeats);
    printf("# Samples: %d\n", dataset->nclasses);

	ml_print_matrix(mlMatrixSumCol(dataset->feats));
}

ml_DataSet* ml_load_csv_dataset(const char *filename, int classPos) {
    ml_CsvFile* csv = ml_load_csv_file(filename, ' ');

    int nsamples = csv->nrow;
    int nfeats = csv->ncol - (classPos<csv->ncol);

    ml_DataSet* dataSet = ml_alloc(ml_DataSet);
    dataSet->nsamples = nsamples;
    dataSet->nfeats = nfeats;
//    dataSet->nclasses = nclasses;

    dataSet->feats = ml_create_matrix(nsamples, nfeats);
    dataSet->label = ml_create_matrix(nsamples, 1);
    dataSet->predict = ml_create_matrix(nsamples, 1);
    dataSet->sample_weight = ml_create_matrix(nsamples, 1);

    dataSet->status = ml_alloc_array(nsamples, ml_SampleStatus);

    float f;
    do {
        f = ml_read_file_float(csv->file);

        if(classPos!=csv->col) {
            ml_mat_elem(dataSet->feats, csv->row, csv->col - (csv->col > classPos)) = f;
        } else {
            ml_mat_elem(dataSet->label, csv->row, 0) = f;
            if(dataSet->nclasses < (f + 1))
                dataSet->nclasses = f + 1;
        }
    } while(ml_next_csv_val(csv));

    dataSet->predict_weight = ml_create_matrix(nsamples, dataSet->nclasses);

    return dataSet;
}

void ml_select_train_samples(ml_DataSet *dataset, float trainPerc) {
    for (int i = 0; i < dataset->nsamples; ++i) {
        float r = ml_rand();
        dataset->status[i] = (r<=trainPerc)? TRAIN : TEST;
    }
}

void ml_free_data_set(ml_DataSet *dataSet) {
	ml_free_matrix(dataSet->feats);
	ml_free_matrix(dataSet->predict);
	ml_free_matrix(dataSet->sample_weight);
	ml_free_matrix(dataSet->predict_weight);
    ml_free(dataSet->status);
	ml_free_matrix(dataSet);
}