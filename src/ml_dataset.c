//
// Created by peixinho on 20/12/16.
//

#include <ml_dataset.h>
#include <ml_memory.h>
#include <ml_csv.h>
#include "ml_matrix.h"
#include "ml_dataset.h"

MlDataSet* mlCreateDataSet(int nsamples, int nfeats, int nclasses) {

    MlDataSet* dataSet = mlAlloc(MlDataSet);
    dataSet->nsamples = nsamples;
    dataSet->nfeats = nfeats;
    dataSet->nclasses = nclasses;

    dataSet->X = mlCreateMatrix(nsamples, nfeats);
    dataSet->Y = mlCreateMatrix(nsamples, 1);
    dataSet->weight = mlCreateMatrix(nsamples, 1);
    dataSet->prob = mlCreateMatrix(nsamples, nclasses);

    dataSet->status = mlAllocArray(nsamples, MlSampleStatus);

    return dataSet;
}

MlDataSet* mlLoadCsvDataSet(const char *filename, int classPos) {
    MlCsvFile* csv = mlLoadCsvFile(filename);

    int nsamples = csv->nrow;
    int nfeats = csv->ncol - (classPos<csv->ncol);

    MlDataSet* dataSet = mlAlloc(MlDataSet);
    dataSet->nsamples = nsamples;
    dataSet->nfeats = nfeats;
//    dataSet->nclasses = nclasses;

    dataSet->X = mlCreateMatrix(nsamples, nfeats);
    dataSet->Y = mlCreateMatrix(nsamples, 1);
    dataSet->weight = mlCreateMatrix(nsamples, 1);
//    dataSet->prob = mlCreateMatrix(nsamples, nclasses);

    dataSet->status = mlAllocArray(nsamples, MlSampleStatus);

    do {
        float f = mlReadFloatFile(csv->file);
        if(classPos!=csv->col) {
            mlMatElem(dataSet->X, csv->row, csv->col - (csv->col > classPos)) = f;
        } else {
            mlMatElem(dataSet->Y, csv->row, 0) = f;
        }

    } while(mlNextCsvVal(csv));

    return dataSet;
}

void mlFreeDataSet(MlDataSet* dataSet) {
    mlFreeMatrix(dataSet->X);
    mlFreeMatrix(dataSet->Y);
    mlFreeMatrix(dataSet->weight);
    mlFreeMatrix(dataSet->prob);
    mlFree(dataSet->status);
    mlFreeMatrix(dataSet);
}