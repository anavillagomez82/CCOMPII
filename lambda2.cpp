#include <iostream>
using namespace std;

char* FuncCad(char* cad, char (*F)(char)) {

    char* ini = cad;

    int tam = 0;
    char* p = ini;
    while (*p != '\0') {
        p++;
        tam++;
    }

    char* fin = ini + tam - 1;

    for (char* q = ini; q <= fin; q++) {
        *q = F(*q);
    }

    return cad;
}

int main() {
  
    char palabra[]  = "HolaMundo";
    char palabra2[] = "HolaMundo";
    auto Upper = [](char c) -> char {
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
      
    };
    auto Lower = [](char c) -> char {
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
    };


    cout << "Upper Case:  " << FuncCad(palabra,  Upper) << endl;
    cout << "Lower Case:  " << FuncCad(palabra2, Lower) << endl;

    return 0;
}
