#include <iostream>
using namespace std;

struct Pila {
    int A[10];     // arreglo fijo de tamaño 10
    int* Top = nullptr; // puntero al elemento "tope" de la pila

    // Verifica si la pila está vacía
    bool vacio() {
        return Top == nullptr;
    }

    // Verifica si la pila está llena
    bool lleno() {
        return Top == A + 9; // último elemento
    }

    // Push: mete un valor a la pila
    bool Push(int val) {
        if (lleno()) return false;

        if (Top) {
            Top++;
        } else {
            Top = A;
        }

        *Top = val;
        return true;
    }

    // Pop: saca un valor de la pila
    bool Pop(int& val) {
        if (vacio()) return false;

        val = *Top;

        if (Top == A) {
            Top = nullptr; // pila vacía
        } else {
            Top--;
        }

        return true;
    }
};

int main() {
    Pila pilaInt;   // pila de enteros
    int a;

    // Agregamos elementos
    pilaInt.Push(5);
    pilaInt.Push(10);
    pilaInt.Push(20);

    // Sacamos un elemento
    if (pilaInt.Pop(a)) {
        cout << "Elemento extraido: " << a << endl;
    } else {
        cout << "La pila está vacía." << endl;
    }

    // Sacamos otro elemento
    if (pilaInt.Pop(a)) {
        cout << "Elemento extraido: " << a << endl;
    } else {
        cout << "La pila está vacía." << endl;
    }

    return 0;
}
