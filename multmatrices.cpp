#include <iostream>
using namespace std;

// Función para multiplicar matrices de 3x3 usando punteros
void multi(int (*p)[3][3]) {
    int (*A)[3] = p[0];   // A apunta a la primera matriz (A)
    int (*B)[3] = p[1];   // B apunta a la segunda matriz (B)
    int (*C)[3] = p[2];   // C apunta a la matriz resultado

    int *pa, *pb, *pc;    // Punteros que usaremos para recorrer A, B y C

    for (int i = 0; i < 3; i++) {         // Recorre las filas de A
        for (int j = 0; j < 3; j++) {     // Recorre las columnas de B
            pc = &C[i][j];                // Apunta a la posición (i, j) de la matriz resultado
            *pc = 0;                      // Inicializa el valor a 0

            // Recorre los elementos de la fila i de A y la columna j de B
            for (int k = 0; k < 3; k++) {
                pa = &A[i][k];             // Elemento en la fila i, columna k de A
                pb = &B[k][j];             // Elemento en la fila k, columna j de B
                *pc += (*pa) * (*pb);      // Suma el producto al resultado
            }
        }
    }
}

int main() {
    // --- Definimos las tres matrices ---
    int A[3][3] = { {1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9} };

    int B[3][3] = { {4, 5, 1},
                    {6, 7, 9},
                    {2, 3, 8} };

    int C[3][3];  // Aquí se guardará el resultado

    // Arreglo de punteros para pasar las tres matrices a la función
    int p[3][3][3] = {0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            p[0][i][j] = A[i][j];   // Primera matriz
            p[1][i][j] = B[i][j];   // Segunda matriz
        }

    multi(p);

    // --- MOSTRAR MATRIZ RESULTADO ---
    cout << "\nMatriz resultado C = A * B:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << p[2][i][j] << " ";
        cout << endl;
    }

    return 0;
}
