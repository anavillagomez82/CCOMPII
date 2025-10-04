#include <iostream>
using namespace std;

void merge(int* p, int* q) {
    int* fin = p + 10;  // apunta al final del array (después del último elemento)

    for (; p < q; p++) {          // p recorre la primera mitad
        for (int* k = q; k < fin; k++) {  // k recorre la segunda mitad
            if (*p > *k) {
                int aux = *p;
                *p = *k;
                *k = aux;
            }
        }
    }
}

int main() {
    int arr[10] = {5, 9, 2, 7, 4, 1, 6, 3, 10, 8};

    int* p = arr;        
    int* q = arr + 5;    

    merge(p, q);

    cout << "Array ordenado: ";
    for (; p < arr + 10; p++) {
        cout << *p << " ";
    }
    cout << endl;

    return 0;
}

    }
    cout << endl;

    return 0;
}
