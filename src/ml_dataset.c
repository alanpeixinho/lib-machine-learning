//
// Created by peixinho on 20/12/16.
//

#include <ml_dataset.h>
#include <ml_memory.h>
#include <ml_csv.h>
#include <ml_matrix.h>
#include <ml_dataset.h>
#include <ml_math.h>

MlDataSet* mlCreateDataSet(int nsamples, int nfeats, int nclasses) {

    MlDataSet* dataSet = mlAlloc(MlDataSet);
    dataSet->nsamples = nsamples;
    dataSet->nfeats = nfeats;
    dataSet->nclasses = nclasses;

    dataSet->feats = mlCreateMatrix(nsamples, nfeats);
    dataSet->label = mlCreateMatrix(nsamples, 1);
    dataSet->predict = mlCreateMatrix(nsamples, 1);
    dataSet->sampleWeight = mlCreateMatrix(nsamples, 1);
    dataSet->predictWeight = mlCreateMatrix(nsamples, nclasses);

    dataSet->status = mlAllocArray(nsamples, MlSampleStatus);

    return dataSet;
}

int mlSamplesNumber(MlDataSet* dataset, MlSampleStatus status) {
    int n = 0;
    for (int i = 0; i < dataset->nsamples; ++i) {
        if(dataset->status[i] & status) {
            n++;
        }
    }
    return n;
}

MlDataSet* mlSelectDataSet(MlDataSet* dataset, MlSampleStatus status) {
    int n = mlSamplesNumber(dataset, status);


    MlDataSet* selected = mlCreateDataSet(n, dataset->nfeats, dataset->nclasses);

    mlSetMatrix(selected->feats, 42);

    int s = 0;
    for (int i = 0; i < dataset->nsamples; ++i) {
        if(dataset->status[i] & status) {
            mlMatElem(selected->sampleWeight, s, 0) = mlMatElem(dataset->sampleWeight, i, 0);
            mlMatElem(selected->label, s, 0) = mlMatElem(dataset->label, i, 0);
            mlMatElem(selected->predict, s, 0) = mlMatElem(dataset->predict, i, 0);

            for (int j = 0; j < dataset->nfeats; ++j) {
                mlMatElem(selected->feats, s, j) = mlMatElem(dataset->feats, i, j);
            }

            for (int c = 0; c < dataset->nclasses; ++c) {
                mlMatElem(selected->predictWeight, s, c) = mlMatElem(dataset->predictWeight, i, c);
            }
            s++;
        }
    }

    return selected;
}

void mlPrintStatsDataSet(MlDataSet* dataset) {
    printf("# Samples: %d, ", dataset->nsamples);
    printf("# Feats: %d, ", dataset->nfeats);
    printf("# Samples: %d\n", dataset->nclasses);

    mlPrintMatrix(mlMatrixSumCol(dataset->feats));
}

MlDataSet* mlLoadCsvDataSet(const char *filename, int classPos) {
    MlCsvFile* csv = mlLoadCsvFile(filename, ' ');

    int nsamples = csv->nrow;
    int nfeats = csv->ncol - (classPos<csv->ncol);

    MlDataSet* dataSet = mlAlloc(MlDataSet);
    dataSet->nsamples = nsamples;
    dataSet->nfeats = nfeats;
//    dataSet->nclasses = nclasses;

    dataSet->feats = mlCreateMatrix(nsamples, nfeats);
    dataSet->label = mlCreateMatrix(nsamples, 1);
    dataSet->predict = mlCreateMatrix(nsamples, 1);
    dataSet->sampleWeight = mlCreateMatrix(nsamples, 1);

    dataSet->status = mlAllocArray(nsamples, MlSampleStatus);

    float f;
    do {
        f = mlReadFloatFile(csv->file);

        if(classPos!=csv->col) {
            mlMatElem(dataSet->feats, csv->row, csv->col - (csv->col > classPos)) = f;
        } else {
            mlMatElem(dataSet->label, csv->row, 0) = f;
            if(dataSet->nclasses < (f + 1))
                dataSet->nclasses = f + 1;
        }
    } while(mlNextCsvVal(csv));

    dataSet->predictWeight = mlCreateMatrix(nsamples, dataSet->nclasses);

    return dataSet;
}

void mlSelectTrainSamples(MlDataSet* dataset, float trainPerc) {
    for (int i = 0; i < dataset->nsamples; ++i) {
        float r = mlRand();
        dataset->status[i] = (r<=trainPerc)? TRAIN : TEST;
    }
}

void mlFreeDataSet(MlDataSet* dataSet) {
    mlFreeMatrix(dataSet->feats);
    mlFreeMatrix(dataSet->predict);
    mlFreeMatrix(dataSet->sampleWeight);
    mlFreeMatrix(dataSet->predictWeight);
    mlFree(dataSet->status);
    mlFreeMatrix(dataSet);
}