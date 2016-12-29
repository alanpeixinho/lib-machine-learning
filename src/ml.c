#include <stdio.h>
#include <ml.h>
#include <ml_matrix.h>
#include <ml_csv.h>
#include <ml_dataset.h>
#include <ml_memory.h>
#include <ml_knn.h>
#include <ml_math.h>

int main() {

    GC_INIT();

	MlMatrix* m = mlCreateMatrix(2, 2);

	mlMatElem(m,0,0) = 1;
    mlMatElem(m,0,1) = 2;
    mlMatElem(m,1,0) = 3;
    mlMatElem(m,1,1) = 4;

    MlMatrix* m2 = mlMultMatrix(m, m);

    mlPrintMatrix(m2);

    MlDataSet* dataset = mlLoadCsvDataSet("/Users/peixinho/mnist.csv", 0);

//    mlPrintMatrix(dataset->feats);
    //mlPrintMatrix(dataset->label);
    mlSelectTrainSamples(dataset, 0.5);

    MlKNN* knn = mlCreateKNN(3);

    mlTrainKNN(knn, dataset);

    int s = 0;
    for (int i = 0; i < 10; ++i) {

        s = mlUniformRand(0,5000);
        printf("-> %d\n", dataset->status[s]);
        float f = mlPredictKNN(knn, mlMatRow(dataset->feats, s));

        printf("%f %f\n", mlMatElem(dataset->label, s, 0), f);

    }

}