//
// Created by peixinho on 20/12/16.
//

#ifndef ML_ML_CSV_H
#define ML_ML_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    FILE* file;

    size_t row;
    size_t col;

    size_t nrow;
    size_t ncol;

    char sep;
} MlCsvFile;

MlCsvFile* mlLoadCsvFile(const char* filename);
bool mlNextCsvVal(MlCsvFile* file);
float mlReadFloatFile(FILE* fp);

#endif //ML_ML_CSV_H
