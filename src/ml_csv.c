//
// Created by peixinho on 20/12/16.
//

#include <ml_csv.h>
#include <ml_memory.h>
#include <stdbool.h>

MlCsvFile* mlLoadCsvFile(const char* filename) {
    MlCsvFile* csv = mlAlloc(MlCsvFile);
    csv->sep = ' ';
    csv->file = fopen(filename, "r");

    mlCountCsvRowCol(csv);

    return csv;
}

void mlCountCsvRowCol(MlCsvFile* csv) {
    csv->ncol = 1;
    csv->nrow = 0;
    char cur, last;
    do {
        cur = fgetc(csv->file);
        if(cur==csv->sep && csv->nrow==0)
            csv->ncol++;
        else if(cur=='\n' && last!='\n')
            csv->nrow++;
        else if(cur==EOF && last!='\n')
            csv->nrow++;
        last = cur;
    } while(cur!=EOF);
    rewind(csv->file);
}

bool mlFindCharFile(FILE* fp, char c) {

    for(;;) {
        char ch = fgetc(fp);
        if(ch == c)
            return true;
        else if(ch==EOF)
            return false;
    }

}

int fpeek(FILE* fp)
{
    const int c = getc(fp);
    return c == EOF ? EOF : ungetc(c, fp);
}

float mlReadFloatFile(FILE* fp) {
    float f;
    fscanf(fp,"%f",&f);
    return f;
}

bool mlNextCsvVal(MlCsvFile* file) {

    if(file->col>0 && file->col<file->ncol-1)
        mlFindCharFile(file->file, file->sep);

    file->col++;

    if(file->col>=file->ncol) {
        file->col = 0;
        file->row++;
    }

    if(file->row>=file->nrow) {
        file->row = 0;
        return false;
    }

    return true;
}