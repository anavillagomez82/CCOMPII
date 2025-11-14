#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string FuncCad(const string &cad, char (*F)(char)) {

    string resultado = cad;
    char *ini = &resultado[0];
    char *fin = ini + resultado.size() - 1;

    for (char *q = ini; q <= fin; q++) {
        *q = F(*q);
    }

    return resultado;
}

int main() {
    string palabra = "HolaMundo";

    auto UPPER = [](char c)->char { return toupper((unsigned char)c); };
    auto LOWER = [](char c)->char { return tolower((unsigned char)c); };


    cout << "Upper Case:  " << FuncCad(palabra, UPPER) <<endl;
    cout << "Lower Case:  " << FuncCad(palabra, LOWER) <<endl;

    return 0;
}
