//quiero que a este codigo le agregues la forma de mergesort con templates y quiero ver el tiempo que demoro cada forma al final 
#include <iostream>
#include <chrono>
using namespace std;

//////////////////////////////
// VERSION 1: NORMAL
//////////////////////////////

void mergeNormal(int arr[], int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[inicio + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSortNormal(int arr[], int inicio, int fin) {
    if (inicio < fin) {
        int medio = (inicio + fin) / 2;

        mergeSortNormal(arr, inicio, medio);
        mergeSortNormal(arr, medio + 1, fin);

        mergeNormal(arr, inicio, medio, fin);
    }
}

//////////////////////////////
// VERSION 2: POLIMORFISMO
//////////////////////////////

class Comparador {
public:
    virtual bool comparar(int a, int b) = 0;
};

class Ascendente : public Comparador {
public:
    bool comparar(int a, int b) {
        return a <= b;
    }
};

void mergePoli(int arr[], int inicio, int medio, int fin, Comparador* comp) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[inicio + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (comp->comparar(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSortPoli(int arr[], int inicio, int fin, Comparador* comp) {
    if (inicio < fin) {
        int medio = (inicio + fin) / 2;

        mergeSortPoli(arr, inicio, medio, comp);
        mergeSortPoli(arr, medio + 1, fin, comp);

        mergePoli(arr, inicio, medio, fin, comp);
    }
}

//////////////////////////////
// VERSION 3: PUNTEROS A FUNCIONES
//////////////////////////////

bool ascendente(int a, int b) {
    return a <= b;
}

void mergeFunc(int arr[], int inicio, int medio, int fin,
               bool (*comparar)(int, int)) {

    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[inicio + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (comparar(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSortFunc(int arr[], int inicio, int fin,
                   bool (*comparar)(int, int)) {

    if (inicio < fin) {
        int medio = (inicio + fin) / 2;

        mergeSortFunc(arr, inicio, medio, comparar);
        mergeSortFunc(arr, medio + 1, fin, comparar);

        mergeFunc(arr, inicio, medio, fin, comparar);
    }
}

//////////////////////////////
// MAIN
//////////////////////////////

int main() {
    const int n = 500000;

    // Es preferible usar 'new' o std::vector para evitar Stack Overflow con n tan grandes
    int* arr1 = new int[n];
    int* arr2 = new int[n];
    int* arr3 = new int[n];

    srand(time(0));

    for (int i = 0; i < n; i++) {
        int num = rand() % 100000;
        arr1[i] = num;
        arr2[i] = num;
        arr3[i] = num;
    }

    // Declaramos las variables de tiempo una sola vez
    std::chrono::high_resolution_clock::time_point inicio, fin;
    std::chrono::duration<double, std::milli> tiempo;

    // NORMAL
    inicio = std::chrono::high_resolution_clock::now();
    mergeSortNormal(arr1, 0, n - 1);
    fin = std::chrono::high_resolution_clock::now();
    tiempo = fin - inicio;
    std::cout << "Merge Normal tardó: " << tiempo.count() << " ms." << std::endl;
    
};
