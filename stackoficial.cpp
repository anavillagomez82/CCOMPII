#include <iostream>
using namespace std;

class Pila {
private:
    int A[10];          
    int* Top = nullptr; // Puntero al tope de la pila

public:
    bool vacio();              
    bool lleno();              
    bool Push(int VAL);        
    bool Pop(int &VAL);        
};

bool Pila::vacio() {
    return Top == nullptr;    // Si Top apunta a nada (nullptr), la pila está vacía
}

bool Pila::lleno() {
    return Top == (A + 9);   // Si Top apunta al último elemento (A + 9), la pila está llena
}

bool Pila::Push(int VAL) {
    if (lleno()) return false;    // Si la pila está llena, no se puede insertar

    if (Top) { // Si Top ya apunta a algún elemento (pila NO vacía)
        Top++; // Avanzamos el puntero al siguiente espacio libre
    } 
    else {
        Top = A; // Si estaba vacía, Top va a apuntar al primer elemento del arreglo
    }

    *Top = VAL; // Guardamos el valor en la posición actual del tope
    return true; 
}

bool Pila::Pop(int &VAL) {
    if (vacio()) return false;    // Si la pila está vacía, no se puede sacar nada

    VAL = *Top;   // Copiamos el valor del tope hacia la variable que recibió la función

    if (Top == A) {    // Si el tope estaba en la primera posición (A)
        Top = nullptr; // La pila queda vacía
    } 
    else {
        Top--; // Si no era el primero, retrocedemos el puntero al elemento anterior
    }

    return true; 
}

int main() {
    Pila pila;   
    int VAL;     

    pila.Push(04);   
    pila.Push(05);  
    pila.Push(20);  

    // Mientras haya elementos en la pila, los extraemos y mostramos
    while (pila.Pop(VAL)) {  // Devuelve true si logra sacar un valor
        cout << "Elemento extraido: " << VAL << endl; // Muestra el valor que sacó
    }

    return 0; 
}
