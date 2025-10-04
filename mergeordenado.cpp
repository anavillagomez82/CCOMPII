#include <iostream>
using namespace std;

void ordenar(int* p, int* q) {
    int* fin = p + 10; // apunta al final del array

    // p recorre desde el inicio hasta el penúltimo elemento
    for (; p < fin - 1; p++) {
        // q recorre desde el siguiente elemento hasta el final
        for (q = p + 1; q < fin; q++) {
            if (*p > *q) {
                int aux = *p;
                *p = *q;
                *q = aux;
            }
        }
    }
}

int main() {
    int arr[10] = {5, 9, 2, 7, 4, 1, 6, 3, 10, 8};

    int* p = arr;        
    int* q = arr + 5;    // inicialmente en la mitad, pero la función lo reutiliza

    ordenar(p, q);

    // reiniciamos p para imprimir desde el inicio
    p = arr;

    cout << "Array ordenado: ";
    for (; p < arr + 10; p++) {
        cout << *p << " ";
    }
    cout << endl;

    return 0;
}
