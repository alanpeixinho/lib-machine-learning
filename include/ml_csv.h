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
} ml_CsvFile;

ml_CsvFile* ml_load_csv_file(const char *filename, char sep);
bool ml_next_csv_val(ml_CsvFile *file);
float ml_read_file_float(FILE *fp);

#endif //ML_ML_CSV_H
