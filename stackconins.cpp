#include <iostream>
using namespace std;

// Clase que implementa una pila (stack) usando un arreglo fijo y un puntero Top.
// Comentarios en cada línea para explicar qué hace.
class Pila {
private:
    int A[10];          // 1) Arreglo fijo que almacena hasta 10 enteros (espacio de la pila).
    int* Top = nullptr; // 2) Puntero al "tope" de la pila. nullptr significa "pila vacía".

public:
    // Verifica si la pila está vacía.
    // Devuelve true si Top es nullptr (no hay elementos).
    bool vacio() {
        return Top == nullptr;
    }

    // Verifica si la pila está llena.
    // Está llena cuando Top apunta al último elemento del arreglo (A + 9).
    bool lleno() {
        return Top == A + 9; // A + 9 es la dirección de A[9]
    }

    // Push: inserta un valor en la pila.
    // Devuelve true si se inserta con éxito, false si la pila está llena.
    bool Push(int val) {
        if (lleno())                // 3) Si ya está llena, no podemos insertar.
            return false;           //    retornamos false (operación fallida).

        if (Top) {                  // 4) Si Top != nullptr => la pila NO está vacía
            Top++;                  //    avanzamos Top al siguiente espacio libre (ej. A[0] -> A[1])
        } else {
            Top = A;                // 5) Si Top == nullptr => pila vacía: inicializamos Top en A (A[0])
        }

        *Top = val;                 // 6) Desreferenciamos Top y guardamos 'val' en esa celda
                                    //    equivalente a: A[pos] = val;
        return true;                // 7) Éxito al insertar
    }

    // Pop: extrae el valor del tope de la pila y lo pone en la variable referenciada por val.
    // Devuelve true si se extrajo con éxito, false si la pila estaba vacía.
    bool Pop(int& val) {
        if (vacio())                // 8) Si la pila está vacía, no hay nada que sacar.
            return false;           //    retornamos false.

        val = *Top;                 // 9) Copiamos el valor del tope a la variable 'val' (por referencia).
                                    //    Como 'val' es referencia, ese cambio queda visible en el llamador.

        if (Top == A) {             // 10) Si Top apunta a A[0], al sacar ese elemento la pila queda vacía.
            Top = nullptr;          //     marcamos la pila como vacía.
        } else {
            Top--;                  // 11) Si no era el primer elemento, retrocedemos Top al elemento anterior.
        }

        return true;                // 12) Éxito en la extracción
    }
};

int main() {
    Pila pilaInt;   // 13) Creamos un objeto Pila (pila de enteros).
    int a;          // 14) Variable donde se guardará el valor extraído con Pop.

    // ---------- Operaciones de ejemplo ----------
    // Insertamos tres valores en orden: 5, 10, 20
    pilaInt.Push(5);   // 15) Insertar 5
    pilaInt.Push(10);  // 16) Insertar 10
    pilaInt.Push(20);  // 17) Insertar 20

    // Extraemos un elemento (debe ser 20: LIFO)
    if (pilaInt.Pop(a)) {             // 18) Pop devuelve true y 'a' contiene el valor extraído
        cout << "Elemento extraído: " << a << endl; // 19) imprime 20
    } else {
        cout << "La pila está vacía." << endl;
    }

    // Extraemos otro elemento (debe ser 10)
    if (pilaInt.Pop(a)) {
        cout << "Elemento extraído: " << a << endl; // imprime 10
    } else {
        cout << "La pila está vacía." << endl;
    }

    // Fin del programa
    return 0;
}
