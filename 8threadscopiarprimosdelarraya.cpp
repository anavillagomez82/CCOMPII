#include <iostream>
#include <thread>
using namespace std;

// Función para saber si un número es primo
bool esPrimo(int n) {
    if (n < 2) return false;
    for (int d = 2; d * d <= n; ++d) {
        if (n % d == 0) return false;
    }
    return true;
}

// Estructura para guardar los primos encontrados por cada thread
struct Resultado {
    int primos[100];  // espacio de sobra
    int count;
    Resultado() : count(0) {}
};

// Cada thread procesa un rango [inicio, fin)
void worker(int *A, int inicio, int fin, Resultado *res) {
    for (int i = inicio; i < fin; ++i) {
        int v = A[i];
        if (esPrimo(v)) {
            res->primos[res->count] = v;
            res->count++;
        }
    }
}

int main() {
    int A[100];

    // Llenamos A con 2,3,4,...,101
    for (int i = 0; i < 100; ++i) {
        A[i] = i + 2;
    }

    const int NUM_THREADS = 8;
    thread hilos[NUM_THREADS];
    Resultado resultados[NUM_THREADS];

    int n = 100;
    int tam_bloque = n / NUM_THREADS;  // 100 / 8 = 12
    int inicio = 0;

    // Creamos los 8 threads, cada uno con un rango distinto
    for (int t = 0; t < NUM_THREADS; ++t) {
        int fin;
        if (t == NUM_THREADS - 1) {
            fin = n;          // el último llega hasta el final
        } else {
            fin = inicio + tam_bloque;
        }

        hilos[t] = thread(worker, A, inicio, fin, &resultados[t]);
        inicio = fin;
    }

    // Esperamos a que terminen
    for (int t = 0; t < NUM_THREADS; ++t) {
        hilos[t].join();
    }

    // Ahora juntamos todos los primos en un array dinámico apuntado por b
    int *b = new int[100];  // máximo 100 primos
    int pos = 0;

    for (int t = 0; t < NUM_THREADS; ++t) {
        for (int i = 0; i < resultados[t].count; ++i) {
            b[pos] = resultados[t].primos[i];
            pos++;
        }
    }

    // Mostramos resultado
    cout << "Primos copiados en b: ";
    for (int i = 0; i < pos; ++i) {
        cout << b[i] << " ";
    }
    cout << endl;

    delete[] b;
    return 0;
}
