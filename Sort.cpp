#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

//////////////////////////////
// VERSION 1: NORMAL
//////////////////////////////

void mergeNormal(int arr[], int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    int* L = new int[n1];
    int* R = new int[n2];
    
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

    delete[] L;
    delete[] R;
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
    virtual ~Comparador() {} // Buen hábito agregar destructor virtual
};

class Ascendente : public Comparador {
public:
    bool comparar(int a, int b) override {
        return a <= b;
    }
};

void mergePoli(int arr[], int inicio, int medio, int fin, Comparador* comp) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    int* L = new int[n1];
    int* R = new int[n2];

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

    delete[] L;
    delete[] R;
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

    int* L = new int[n1];
    int* R = new int[n2];

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

    delete[] L;
    delete[] R;
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
// VERSION 4: TEMPLATES (PLANTILLAS)
//////////////////////////////

// Estructura functor para pasar como argumento de plantilla
//Esta version de templates quiero que la modifiques no uses typename sino class, y tiene que haber 2 struct un cless que tendra solo un metodo bool cmp y que comparara dos numeros en este caso si es menor uno que otro y el toro struct es un cgreater que sera igual solo que comparar si es mayor,cada uno con su template antes 
template <typename T>
struct ComparadorTemplate {
    bool operator()(const T& a, const T& b) const {
        return a <= b;
    }
};

template <typename T, typename Compare>
void mergeTemplate(T arr[], int inicio, int medio, int fin, Compare comp) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    // Reservamos memoria dinámica para evitar desbordamiento de pila (Stack Overflow)
    T* L = new T[n1];
    T* R = new T[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[inicio + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (comp(L[i], R[j]))  // Se evalúa en tiempo de compilación (o inline)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

template <typename T, typename Compare>
void mergeSortTemplate(T arr[], int inicio, int fin, Compare comp) {
    if (inicio < fin) {
        int medio = (inicio + fin) / 2;

        mergeSortTemplate(arr, inicio, medio, comp);
        mergeSortTemplate(arr, medio + 1, fin, comp);

        mergeTemplate(arr, inicio, medio, fin, comp);
    }
}

//////////////////////////////
// MAIN
//////////////////////////////

int main() {
    const int n = 500000;

    // Memoria dinámica para los 4 arreglos idénticos
    int* arr1 = new int[n];
    int* arr2 = new int[n];
    int* arr3 = new int[n];
    int* arr4 = new int[n];

    srand(time(0));

    for (int i = 0; i < n; i++) {
        int num = rand() % 100000;
        arr1[i] = num;
        arr2[i] = num;
        arr3[i] = num;
        arr4[i] = num;
    }

    // Variables para medir el rendimiento
    std::chrono::high_resolution_clock::time_point inicio, fin;
    double t_normal, t_poli, t_func, t_template;

    // 1. RENDIMIENTO MERGE NORMAL
    inicio = std::chrono::high_resolution_clock::now();
    mergeSortNormal(arr1, 0, n - 1);
    fin = std::chrono::high_resolution_clock::now();
    t_normal = std::chrono::duration<double, std::milli>(fin - inicio).count();

    // 2. RENDIMIENTO MERGE POLIMORFISMO
    Comparador* compPoli = new Ascendente();
    inicio = std::chrono::high_resolution_clock::now();
    mergeSortPoli(arr2, 0, n - 1, compPoli);
    fin = std::chrono::high_resolution_clock::now();
    t_poli = std::chrono::duration<double, std::milli>(fin - inicio).count();
    delete compPoli;

    // 3. RENDIMIENTO MERGE PUNTERO A FUNCIÓN
    inicio = std::chrono::high_resolution_clock::now();
    mergeSortFunc(arr3, 0, n - 1, ascendente);
    fin = std::chrono::high_resolution_clock::now();
    t_func = std::chrono::duration<double, std::milli>(fin - inicio).count();

    // 4. RENDIMIENTO MERGE TEMPLATES
    ComparadorTemplate<int> compTemplate;
    inicio = std::chrono::high_resolution_clock::now();
    mergeSortTemplate(arr4, 0, n - 1, compTemplate);
    fin = std::chrono::high_resolution_clock::now();
    t_template = std::chrono::duration<double, std::milli>(fin - inicio).count();

    // IMPRESIÓN DE RESULTADOS FINALES
    cout << "================================================" << endl;
    cout << "   COMPARATIVA DE TIEMPOS DE EJECUCIÓN (N=" << n << ")" << endl;
    cout << "================================================" << endl;
    cout << "1. Merge Sort Normal (Directo):     " << t_normal   << " ms." << endl;
    cout << "2. Merge Sort Polimorfismo:         " << t_poli     << " ms." << endl;
    cout << "3. Merge Sort Puntero a Función:    " << t_func     << " ms." << endl;
    cout << "4. Merge Sort con Templates:        " << t_template << " ms." << endl;
    cout << "================================================" << endl;

    // Liberación de memoria principal
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;

    return 0;
}
