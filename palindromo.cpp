#include <iostream>
using namespace std;

bool palindromo(char* c) {
    char* p = c;   // Apunta al inicio
    char* f = c;   // También apunta al inicio, pero lo moveremos hasta el final
    bool pal = true;

    // Calcula la longitud de la cadena
    while (*f != '\0') {  // Mientras no llegue al final de la cadena
        f++;              // Avanza el puntero
    }
    f--;  // Retrocede una posición para apuntar al último carácter válido

    // Compara los extremos
    for (; p < f; p++, f--) {
        if (*p != *f) {
            pal = false;
            break;
        }
    }

    return pal;
}

int main() {
    char A[3][50] = {
        "Hola mundo",
        "anita lava la tina",
        "oso"
    };

    for (char* p = *A; p < *A + 3 * 50; p += 50) {
        if (palindromo(p))
            cout << p << "  ->  SI es palindromo" << endl;
        else
            cout << p << "  ->  NO es palindromo" << endl;
    }

    return 0;
}
