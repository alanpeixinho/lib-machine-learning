#include <stdio.h>
#include <ml.h>
#include <ml_matrix.h>
#include <ml_csv.h>
#include <ml_dataset.h>

int main() {
	MlMatrix* m = mlCreateMatrix(2, 2);

	mlMatElem(m,0,0) = 1;
    mlMatElem(m,0,1) = 2;
    mlMatElem(m,1,0) = 3;
    mlMatElem(m,1,1) = 4;

    MlMatrix* m2 = mlMultMatrix(m, m);

    mlPrintMatrix(m2);

    MlDataSet* dataset = mlLoadCsvDataSet("csv.csv", 0);

    mlPrintMatrix(dataset->X);
    mlPrintMatrix(dataset->Y);

}