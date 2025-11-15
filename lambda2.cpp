#include <iostream>
#include <cctype>
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

    auto UPPER = [](char c)->char { return toupper((unsigned char)c); };
    auto LOWER = [](char c)->char { return tolower((unsigned char)c); };

    cout << "Upper Case:  " << FuncCad(palabra,  UPPER) << endl;
    cout << "Lower Case:  " << FuncCad(palabra2, LOWER) << endl;

    return 0;
}


#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string FuncCad(const string &cad, char (*F)(char)) {

    string resultado = cad;
    char *ini = &resultado[0];
    int tam = 0;
    char* p=ini;
    while (*p != '\0') {
    p++;
    tam++;}
    char *fin = ini + tam - 1;

    for (char *q = ini; q <= fin; q++) {
        *q = F(*q);
    }

    return resultado;
}

int main() {
    string palabra = "HolaMundo";

    auto UPPER = [](char c)->char { return toupper((char)c); };
    auto LOWER = [](char c)->char { return tolower((char)c); };


    cout << "Upper Case:  " << FuncCad(palabra, UPPER) <<endl;
    cout << "Lower Case:  " << FuncCad(palabra, LOWER) <<endl;

    return 0;
}


