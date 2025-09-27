#include <iostream>
#include <cstring>
#include <cctype>  // para tolower
using namespace std;

bool Palindromo(char* c) {
    char* p = c;
    char* f = c + strlen(c) - 1;

    while (p < f) {
        if (*p == ' ') { p++; continue; }
        if (*f == ' ') { f--; continue; }

        if (tolower(*p) != tolower(*f)) {
            return false;
        }

        p++;
        f--;
    }
    return true;
}

int main() {
    char A[3][50] = {
        "Hola Amigos",
        "anita lava la tina",
        "amo la paloma"
    };

    for (char* p = *A; p < *A + 3 * 50; p += 50) {
        cout << "Frase: " << p << " -> ";
        if (Palindromo(p))
            cout << "Es palindromo";
        else
            cout << "No es palindromo";
        cout << endl;
    }

    return 0;
}
