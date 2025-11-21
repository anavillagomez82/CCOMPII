#include <iostream>
#include <pthread.h>
using namespace std;

#define N 10

char M[N][N] = {
    {'A','T','L','E','T','I','A','A','A','A'},
    {'T','A','A','A','A','A','A','A','A','A'},
    {'L','A','A','A','A','A','A','O','A','A'}, 
    {'E','A','A','A','A','A','A','T','A','A'},
    {'T','A','A','A','A','I','A','L','A','A'},
    {'I','A','A','A','A','T','A','E','A','A'},
    {'A','A','A','A','A','E','A','T','A','A'},
    {'A','A','A','A','A','L','A','I','A','A'}, 
    {'A','A','A','A','A','T','A','A','A','A'},
    {'I','T','E','L','T','A','A','A','A','A'}
};

char palabras[][10] = {"ATLETI", "TEL", "ITA", "AE", "TA"};
int num_palabras = 5;

int largo(const char p[]) {
    int c = 0;
    while (p[c] != '\0') c++;
    return c;
}

struct Datos {
    int resultados[20];
};

// Izquierda → Derecha
void* buscar_izq_der(void* arg){
    Datos* D = (Datos*)arg;

    for (int w = 0; w < num_palabras; w++) {
        int L = largo(palabras[w]);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= N-L; j++) {
                int k;
                for (k = 0; k < L; k++)
                    if (M[i][j+k] != palabras[w][k]) break;

                if (k == L) D->resultados[w]++;
            }
        }
    }
    return NULL;
}

// Derecha → Izquierda
void* buscar_der_izq(void* arg){
    Datos* D = (Datos*)arg;

    for (int w = 0; w < num_palabras; w++) {
        int L = largo(palabras[w]);

        for (int i = 0; i < N; i++) {
            for (int j = L - 1; j < N; j++) {
                int k;
                for (k = 0; k < L; k++)
                    if (M[i][j-k] != palabras[w][k]) break;

                if (k == L) D->resultados[w]++;
            }
        }
    }
    return NULL;
}

// Arriba → Abajo
void* buscar_arr_ab(void* arg){
    Datos* D = (Datos*)arg;

    for (int w = 0; w < num_palabras; w++) {
        int L = largo(palabras[w]);

        for (int i = 0; i <= N-L; i++) {
            for (int j = 0; j < N; j++) {
                int k;
                for (k = 0; k < L; k++)
                    if (M[i+k][j] != palabras[w][k]) break;

                if (k == L) D->resultados[w]++;
            }
        }
    }
    return NULL;
}

// Abajo → Arriba
void* buscar_ab_arr(void* arg){
    Datos* D = (Datos*)arg;

    for (int w = 0; w < num_palabras; w++) {
        int L = largo(palabras[w]);

        for (int i = L-1; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int k;
                for (k = 0; k < L; k++)
                    if (M[i-k][j] != palabras[w][k]) break;

                if (k == L) D->resultados[w]++;
            }
        }
    }
    return NULL;
}

int main(){

    pthread_t t1, t2, t3, t4;

    Datos D1 = {0};
    Datos D2 = {0};
    Datos D3 = {0};
    Datos D4 = {0};

    pthread_create(&t1, NULL, buscar_izq_der, &D1);
    pthread_create(&t2, NULL, buscar_der_izq, &D2);
    pthread_create(&t3, NULL, buscar_arr_ab, &D3);
    pthread_create(&t4, NULL, buscar_ab_arr, &D4);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    for (int w = 0; w < num_palabras; w++) {
        int total =D1.resultados[w] + D2.resultados[w] + D3.resultados[w] + D4.resultados[w];

        cout << "Palabra: " << palabras[w] << "\n";
        cout << "  Izq → Der : " << D1.resultados[w] << "\n";
        cout << "  Der → Izq : " << D2.resultados[w] << "\n";
        cout << "  Arr → Ab  : " << D3.resultados[w] << "\n";
        cout << "  Ab → Arr  : " << D4.resultados[w] << "\n";
        cout << "  TOTAL     : " << total << "\n\n";
    }

    return 0;
}
