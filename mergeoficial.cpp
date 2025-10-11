#include <iostream>
using namespace std;

void merge(int* p, int* q) {
    int temp[10];        // array temporal
    int* t = temp;       // puntero que llenará el array temporal
    int* fin = q + 5;    

    int* mitad = q;     

    // Comparar p y q
    while (p < mitad && q < fin) {
        if (*p <= *q) {
            *t = *p;
            p++;
        } else {
            *t = *q;
            q++;
        }
        t++;
    }

    // Si aún quedan elementos en la primera mitad
    while (p < mitad) {
        *t = *p;
        p++;
        t++;
    }

    // Si aún quedan elementos en la segunda mitad
    while (q < fin) {
        *t = *q;
        q++;
        t++;
    }

    // Copiar el array temporal al original
    for (int i = 0; i < 10; i++) {
        *(mitad - 5 + i) = temp[i];
    }
}

int main() {
    int arr[10] = {2, 4, 6, 8, 10, 1, 3, 5, 7, 9};

    int* p = arr;       
    int* q = arr + 5;   

    merge(p, q);

    cout << "Array combinado y ordenado: ";
    for (int* it = arr; it < arr + 10; it++) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
