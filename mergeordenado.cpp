#include <iostream>
using namespace std;

void ordenar(int* p, int* q) {
    // p recorre desde el inicio al penúltimo elemento
    for (; p < (q + 5) - 1; p++) {   // q + 5 == arr + 10
        // r recorre desde el siguiente elemento de p hasta el final
        for (int* r = p + 1; r < (q + 5); r++) {
            if (*p > *r) {
                int aux = *p;
                *p = *r;
                *r = aux;
            }
        }
    }
}

int main() {
    int arr[10] = {5, 9, 2, 7, 4, 1, 6, 3, 10, 8};

    int* p = arr;        
    int* q = arr + 5;    

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
