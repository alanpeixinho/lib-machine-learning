#include <stdio.h>
#include <ml.h>
#include <ml_matrix.h>

int main() {
	MlMatrix* m = mlCreateMatrix(2, 2);

	m->data[0]=1;
	m->data[1]=2;
	m->data[2]=3;
	m->data[3]=4;

	MlMatrix* m2 = mlMultMatrix(m, m);

    for (int i = 0; i < m2->n; ++i) {
        printf("%f ", m2->data[i]);
    }
    printf("\n");

}