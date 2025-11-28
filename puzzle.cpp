#include <iostream>
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

int buscarPosVacio(int *m, int N) {
    int total = N * N;
    for (int k = 0; k < total; ++k) {
        if (*(m + k) == 0)
            return k;
    }
    return -1; 
}

bool estaOrdenado(int *m, int N) {
    int esperado = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == N - 1 && j == N - 1) {
                return (celda(m, N, i, j) == 0);
            }
            if (celda(m, N, i, j) != esperado)
                return false;
            ++esperado;
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

    if (tecla == 'w')      nf = fila - 1;   // arriba
    else if (tecla == 's') nf = fila + 1;   // abajo
    else if (tecla == 'a') nc = col  - 1;   // izquierda
    else if (tecla == 'd') nc = col  + 1;   // derecha
    else return false; // tecla inválida

    // Si mueve fuera del tablero
    if (nf < 0 || nf >= N || nc < 0 || nc >= N)
        return false;

    // Intercambiar casilla vacía con la casilla destino
    int &vacio   = celda(m, N, fila, col);
    int &destino = celda(m, N, nf, nc);

    int temp  = destino;
    destino   = vacio;
    vacio     = temp;

    return true;
}

// "Mezcla" determinista: intercambia pares de elementos
// en las primeras N^2 - 1 posiciones (sin tocar la última, que es 0)
void mezclarDeterminista(int *m, int N) {
    int total = N * N - 1; // hasta la casilla antes del 0
    for (int k = 0; k + 1 < total; k += 2) {
        int temp     = *(m + k);
        *(m + k)     = *(m + k + 1);
        *(m + k + 1) = temp;
    }
}

// Crea un tablero inicial NxN: números desordenados y 0 al final
int* crearTableroInicial(int N) {
    int total = N * N;
    int *m = new int[total];

    // Llenamos 1..N^2-1
    for (int k = 0; k < total - 1; ++k) {
        *(m + k) = k + 1;
    }
    // Última casilla vacía (al final)
    *(m + (total - 1)) = 0;

    // Desordenamos las primeras N^2-1 posiciones de forma determinista
    mezclarDeterminista(m, N);

    return m;
}

int main() {
    int N;
    cout << "Ingrese el tamano N de la matriz (N x N): ";
    cin >> N;

    if (N < 2) {
        cout << "N debe ser al menos 2.\n";
        return 0;
    }

    int *tablero = crearTableroInicial(N);

    cout << "\nJuego del rompecabezas (w/a/s/d para mover, q para salir)\n";

    while (true) {
        imprimirTablero(tablero, N);

        if (estaOrdenado(tablero, N)) {
            cout << "¡Felicidades, ordenaste la matriz!\n";
            break;
        }

        cout << "Movimiento (w/a/s/d, q para salir): ";
        char tecla;
        if (!(cin >> tecla)) {
            cout << "\nEntrada terminada. Saliendo...\n";
            break;
        }

        if (tecla == 'q' || tecla == 'Q') {
            cout << "Saliendo del juego...\n";
            break;
        }

        bool ok = moverVacio(tablero, N, tecla);
        if (!ok) {
            cout << "Movimiento invalido.\n";
        }
    }

    delete[] tablero;

    return 0;
}
