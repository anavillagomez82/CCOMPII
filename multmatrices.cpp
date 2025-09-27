#include <iostream>
using namespace std;

int main() {
    const int N = 3;
    int A[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int B[N][N] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    int C[N][N] = {0}; // Resultado

    // Multiplicación usando punteros
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *(*(C + i) + j) = 0; // inicializamos
            for (int k = 0; k < N; k++) {
                *(*(C + i) + j) += (*(*(A + i) + k)) * (*(*(B + k) + j));
            }
        }
    }

    // Imprimir matriz resultado
    cout << "Matriz resultante (A x B):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << *(*(C + i) + j) << " ";
        }
        cout << endl;
    }

    return 0;
}
