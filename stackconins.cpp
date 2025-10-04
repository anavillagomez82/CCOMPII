#include <iostream>
using namespace std;

class Pila {
private:
    int A[10];         
    int* Top = nullptr; 

public:
    // Verifica si la pila está vacía.
    bool vacio() {
        return Top == nullptr;
    }

    // Verifica si la pila está llena.
    bool lleno() {
        return Top == A + 9; // A + 9 es la dirección de A[9]
    }

    // Push: inserta un valor en la pila.
   
    bool Push(int val) { // Devuelve true si se inserta con éxito, false si la pila está llena.
        if (lleno())               
            return false;          

        if (Top) {                  //  Si Top != nullptr => la pila NO está vacía
            Top++;                 
        } else {
            Top = A;                // Si Top == nullptr => pila vacía
        }

        *Top = val;                 
                                    
        return true;                //  Éxito al insertar
    }

    // Pop: extrae el valor del tope de la pila y lo pone en la variable referenciada por val.
    // Devuelve true si se extrajo con éxito, false si la pila estaba vacía.
    bool Pop(int& val) {
        if (vacio())                
            return false;          

        val = *Top;                
                                    // Como 'val' es referencia, ese cambio queda visible en el llamador.

        if (Top == A) {             // Si Top apunta a A[0], al sacar ese elemento la pila queda vacía.
            Top = nullptr;          //     marcamos la pila como vacía.
        } else {
            Top--;                 
        }

        return true;                // Éxito en la extracción
    }
};

int main() {
    Pila pilaInt;   
    int a;          // donde se guardará el valor extraído con Pop.

    pilaInt.Push(5);   
    pilaInt.Push(10);  
    pilaInt.Push(20);  

    // Extraemos el 20: LIFO
    if (pilaInt.Pop(a)) {             // Pop devuelve true y 'a'
        cout << "Elemento extraído: " << a << endl;
    } else {
        cout << "La pila está vacía." << endl;
    }

    // Extraemos el 10
    if (pilaInt.Pop(a)) {
        cout << "Elemento extraído: " << a << endl; // imprime 10
    } else {
        cout << "La pila está vacía." << endl;
    }
    return 0;
}
