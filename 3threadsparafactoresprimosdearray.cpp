#include <iostream>
#include <thread>
using namespace std;

// Función que imprime los factores primos de un número
void factorizar(int x) {
    cout << x << " = ";

    int divisor = 2;
    while (x > 1) {
        while (x % divisor == 0) {
            cout << divisor << " ";
            x /= divisor;
        }
        divisor++;
    }

    cout << endl;
}

// Procesa una parte del arreglo
void procesar(int *arr, int inicio, int fin) {
    for (int i = inicio; i <= fin; i++) {
        factorizar(arr[i]);
    }
}

int main() {
    int a[11] = {15,23,2,3,6,5,72,100,35,8,11};

    // Thread 1 procesa elementos 0–3
    thread t1(procesar, a, 0, 3);

    // Thread 2 procesa elementos 4–7
    thread t2(procesar, a, 4, 7);

    // Thread 3 procesa elementos 8–10
    thread t3(procesar, a, 8, 10);

    // Esperamos a que todos terminen
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
