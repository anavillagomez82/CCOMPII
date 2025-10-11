#include <iostream>
#include <cctype>  // para tolower()
using namespace std;

bool palindromo(char* c) {
    char* p = c;   // puntero al inicio
    char* f = c;   // puntero que recorrerá hasta el final
    bool pal = true;

    // Calcula la longitud de la cadena
    while (*f != '\0') {
        f++;
    }
    f--;  // retrocede al último carácter válido

    // Compara ignorando espacios y mayúsculas
    while (p < f) {
        // saltar espacios y caracteres no alfabéticos al inicio
        if (!isalpha(*p)) {
            p++;
            continue;
        }

        // saltar espacios y caracteres no alfabéticos al final
        if (!isalpha(*f)) {
            f--;
            continue;
        }

        // comparar sin distinguir mayúsculas
        if (tolower(*p) != tolower(*f)) {
            pal = false;
            break;
        }

        p++;
        f--;
    }

    return pal;
}

int main() {
    char A[3][50] = {
        "Hola mundo",
        "anita lava la tina",
        "Oso"
    };

    for (int i = 0; i < 3; i++) {
        if (palindromo(A[i]))
            cout << A[i] << "  ->  SI es palindromo" << endl;
        else
            cout << A[i] << "  ->  NO es palindromo" << endl;
    }

    return 0;
}
