#include <iostream>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
using namespace std;

int& celda(int *m, int N, int fila, int col) {
    return *(m + fila * N + col);
}

void imprimirTablero(int *m, int N) {
    cout << "\n-----------------\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int valor = celda(m, N, i, j);
            if (valor == 0)
                cout << "  ";
            else
                cout << valor << " ";
        }
        cout << "\n";
    }
    cout << "-----------------\n";
}

// Busca la posición de la casilla vacía (0)
int buscarPosVacio(int *m, int N) {
    int total = N * N;
    for (int k = 0; k < total; ++k)
        if (*(m + k) == 0)
            return k;
    return -1;
}

// Verifica si ya está ordenado
bool estaOrdenado(int *m, int N) {
    int esperado = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == N - 1 && j == N - 1)
                return (celda(m, N, i, j) == 0);
            if (celda(m, N, i, j) != esperado)
                return false;
            esperado++;
        }
    }
    return true;
}
bool moverVacio(int *m, int N, char tecla) {
    int pos = buscarPosVacio(m, N);
    if (pos == -1) return false;

    int fila = pos / N;
    int col  = pos % N;

    int nf = fila;
    int nc = col;

    if (tecla == 'w') nf = fila - 1;
    else if (tecla == 's') nf = fila + 1;
    else if (tecla == 'a') nc = col - 1;
    else if (tecla == 'd') nc = col + 1;
    else return false;

    if (nf < 0 || nf >= N || nc < 0 || nc >= N)
        return false;

    int &vacio   = celda(m, N, fila, col);
    int &destino = celda(m, N, nf, nc);

    int temp = destino;
    destino  = vacio;
    vacio    = temp;

    return true;
}

void mezclarRandom(int *m, int N) {
    int total = N * N;

    for (int k = total - 2; k > 0; --k) {
        int j = rand() % (k + 1); 
        int temp   = *(m + k);
        *(m + k)   = *(m + j);
        *(m + j)   = temp;
    }
}

int* crearTableroInicial(int N) {
    int total = N * N;
    int *m = new int[total];
    for (int k = 0; k < total - 1; ++k)
        *(m + k) = k + 1;
    *(m + (total - 1)) = 0;
    mezclarRandom(m, N);
    return m;
}

int main() {
    int N;
    cout << "Ingrese el tamaño de la matriz (N x N): ";
    cin >> N;

    if (N < 2) {
        cout << "N debe ser al menos 2.\n";
        return 0;
    }
    srand((unsigned)time(nullptr));

    int *tablero = crearTableroInicial(N);

    cout << "\nPuzzle del rompecabezas (w/a/s/d para mover, x para salir)\n";

    while (true) {
        imprimirTablero(tablero, N);

        if (estaOrdenado(tablero, N)) {
            cout << "¡Felicidades, ordenaste la matriz!\n";
            break;
        }

        cout << "Movimiento: ";
        char tecla;
        cin >> tecla;

        if (tecla == 'x' || tecla == 'X')
            break;

        if (!moverVacio(tablero, N, tecla))
            cout << "Movimiento invalido.\n";
    }

    delete[] tablero;
    return 0;
}
