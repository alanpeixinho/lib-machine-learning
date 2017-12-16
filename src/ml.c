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

	MlMatrix* m = ml_create_matrix(2, 2);

	ml_mat_elem(m,0,0) = 1;
    ml_mat_elem(m,0,1) = 2;
    ml_mat_elem(m,1,0) = 3;
    ml_mat_elem(m,1,1) = 4;

    MlMatrix* m2 = mlMultMatrix(m, m);

	ml_print_matrix(m2);

    ml_DataSet* dataset = ml_load_csv_dataset("/Users/peixinho/mnist.csv", 0);

//    ml_print_matrix(dataset->feats);
    //ml_print_matrix(dataset->label);
	ml_select_train_samples(dataset, 0.5);

    ml_KNN* knn = ml_create_knn(3);

	ml_train_knn(knn, dataset);

    int s = 0;
    for (int i = 0; i < 10; ++i) {

        s = ml_uniform_rand(0, 5000);
        printf("-> %d\n", dataset->status[s]);
        float f = ml_predict_knn(knn, ml_mat_row(dataset->feats, s));

        printf("%f %f\n", ml_mat_elem(dataset->label, s, 0), f);
    }

}