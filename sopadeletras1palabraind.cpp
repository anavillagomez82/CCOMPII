#include <iostream>
#include <pthread.h>
using namespace std;

int count_izq_der = 0;
int count_der_izq = 0;
int count_arr_ab = 0;
int count_ab_arr = 0;

char palabra[] = "ATLETI";

int largo(const char* p) {
    int c = 0;
    while (p[c] != '\0') c++;
    return c;
}

void* buscar_izq_der(void* arg){
    char (*M)[10] = (char (*)[10])arg;
    int W = largo(palabra);

    for(int i=0;i<10;i++){
        for(int j=0; j<=10-W; j++){
            int k;
            for(k=0;k<W;k++){
                if(M[i][j+k] != palabra[k]) break;
            }
            if(k==W) count_izq_der++;
        }
    }
    return NULL;
}
void* buscar_der_izq(void* arg){
    char (*M)[10] = (char (*)[10])arg;
    int W = largo(palabra);

    for(int i=0;i<10;i++){
        for(int j=W-1; j<10; j++){
            int k;
            for(k=0;k<W;k++){
                if(M[i][j-k] != palabra[k]) break;
            }
            if(k==W) count_der_izq++;
        }
    }
    return NULL;
}
void* buscar_arr_ab(void* arg){
    char (*M)[10] = (char (*)[10])arg;
    int W = largo(palabra);

    for(int i=0;i<=10-W;i++){
        for(int j=0;j<10;j++){
            int k;
            for(k=0;k<W;k++){
                if(M[i+k][j] != palabra[k]) break;
            }
            if(k==W) count_arr_ab++;
        }
    }
    return NULL;
}
void* buscar_ab_arr(void* arg){
    char (*M)[10] = (char (*)[10])arg;
    int W = largo(palabra);

    for(int i=W-1;i<10;i++){
        for(int j=0;j<10;j++){
            int k;
            for(k=0;k<W;k++){
                if(M[i-k][j] != palabra[k]) break;
            }
            if(k==W) count_ab_arr++;
        }
    }
    return NULL;
}

int main(){
    char M[10][10] = {
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

    pthread_t t1, t2, t3, t4;

    pthread_create(&t1, NULL, buscar_izq_der, (void*)M);
    pthread_create(&t2, NULL, buscar_der_izq, (void*)M);
    pthread_create(&t3, NULL, buscar_arr_ab, (void*)M);
    pthread_create(&t4, NULL, buscar_ab_arr, (void*)M);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    cout << "Izquierda → Derecha: " << count_izq_der << endl;
    cout << "Derecha → Izquierda: " << count_der_izq << endl;
    cout << "Arriba → Abajo: " << count_arr_ab << endl;
    cout << "Abajo → Arriba: " << count_ab_arr << endl;

    int total = count_izq_der + count_der_izq + count_arr_ab + count_ab_arr;
    cout << "\nTotal encontrado: " << total << " veces\n";

    return 0;
}
