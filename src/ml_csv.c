//
// Created by peixinho on 20/12/16.
//

#include <ml_csv.h>
#include <ml_memory.h>
#include <stdbool.h>
#include <ml_common.h>

void ml_count_csv_row_col(ml_CsvFile *csv) {
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

ml_CsvFile* ml_load_csv_file(const char *filename, char sep) {
    ml_CsvFile* csv = ml_alloc(ml_CsvFile);
    csv->sep = sep;
    csv->file = fopen(filename, "r");

    if(csv->file == NULL) {
        ml_throw_error("File not found", "ml_load_csv_file()");
    }

	ml_count_csv_row_col(csv);

    return csv;
}

bool ml_find_sep(FILE *fp, char c) {

    for(;;) {
        char ch = fgetc(fp);
        if(ch == c) {
//            ungetc(ch, fp);
            return true;
        }
        else if(ch==EOF) {
            return false;
        }
        else if(ch=='\n') {
            return false;
        }
    }

}

int fpeek(FILE* fp)
{
    const int c = getc(fp);
    return c == EOF ? EOF : ungetc(c, fp);
}

float ml_read_file_float(FILE *fp) {
    float f;
    fscanf(fp,"%f",&f);
    return f;
}

bool ml_next_csv_val(ml_CsvFile *file) {

    //if(file->col>0 && file->col<file->ncol-1)
    if(file->sep!=' ')
	    ml_find_sep(file->file, file->sep);

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
