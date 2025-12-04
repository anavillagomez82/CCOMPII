#include <iostream>
#include <thread>
using namespace std;

// Calcula una fila de la matriz C = A * B
void calcularFila(int A[3][3], int B[3][3], int C[3][3], int fila) {
    for (int j = 0; j < 3; ++j) {      // columnas de B
        C[fila][j] = 0;
        for (int k = 0; k < 3; ++k) {  // suma A[fila][k] * B[k][j]
            C[fila][j] += A[fila][k] * B[k][j];
        }
    }
}

int main() {
    int A[3][3] = {
        {1, 3, 5},
        {7, 9, 11},
        {13, 15, 17}
    };

    int B[3][3] = {
        {2, 4, 6},
        {8, 10, 12},
        {14, 16, 18}
    };

    int C[3][3]; // resultado

    // Creamos 3 threads, uno por fila
    thread t0(calcularFila, A, B, C, 0);  // fila 0
    thread t1(calcularFila, A, B, C, 1);  // fila 1
    thread t2(calcularFila, A, B, C, 2);  // fila 2

    // Esperamos a que terminen
    t0.join();
    t1.join();
    t2.join();

    // Mostramos la matriz resultado
    cout << "Matriz C = A * B:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
