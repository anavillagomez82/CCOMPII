#include <iostream>
using namespace std;

void multi(int (*p)[3][3]) {

    for (int i = 0; i < 3; i++) {          // Filas de A
        for (int j = 0; j < 3; j++) {      // Columnas de B
            *(*(p[2] + i) + j) = 0;        // Inicializa C[i][j] = 0

            for (int k = 0; k < 3; k++) {  // Recorre fila de A y columna de B
                *(*(p[2] + i) + j) += *(*(p[0] + i) + k) * *(*(p[1] + k) + j);
            }
        }
    }
}

int main() {
    int A[3][3] = { {1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9} };

    int B[3][3] = { {4, 5, 1},
                    {6, 7, 9},
                    {2, 3, 8} };

    int C[3][3] = {0};

    int p[3][3][3] = {0};

    // Se copia A y B dentro del arreglo p
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            p[0][i][j] = A[i][j];
            p[1][i][j] = B[i][j];
        }

    multi(p);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << p[2][i][j] << " ";
        cout << endl;
    }

    return 0;
}

