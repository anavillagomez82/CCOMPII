#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

// =====================================================
// GENERAR ARRAY RANDOM CON CHRONO
// =====================================================

void generarArray(vector<int>& arr, int n)
{
    arr.resize(n);

    unsigned seed =
        chrono::system_clock::now().time_since_epoch().count();

    mt19937 gen(seed);

    uniform_int_distribution<int> dist(0, 100000);

    for(int i = 0; i < n; i++)
    {
        arr[i] = dist(gen);
    }
}

// =====================================================
// 1. MERGE SORT NORMAL
// =====================================================

void mergeNormal(vector<int>& arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

void mergeSortNormal(vector<int>& arr, int l, int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;

        mergeSortNormal(arr, l, m);
        mergeSortNormal(arr, m + 1, r);

        mergeNormal(arr, l, m, r);
    }
}

// =====================================================
// 2. PUNTEROS A FUNCIONES
// =====================================================

bool menorFuncion(int a, int b)
{
    return a <= b;
}

void mergeFuncion(vector<int>& arr, int l, int m, int r,
                  bool (*cmp)(int, int))
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2)
    {
        if(cmp(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

void mergeSortFuncion(vector<int>& arr, int l, int r,
                      bool (*cmp)(int, int))
{
    if(l < r)
    {
        int m = (l + r) / 2;

        mergeSortFuncion(arr, l, m, cmp);
        mergeSortFuncion(arr, m + 1, r, cmp);

        mergeFuncion(arr, l, m, r, cmp);
    }
}

// =====================================================
// 3. POLIMORFISMO
// =====================================================

class Comparador
{
public:
    virtual bool comparar(int a, int b) = 0;
};

class Menor : public Comparador
{
public:
    bool comparar(int a, int b) override
    {
        return a <= b;
    }
};

void mergePoli(vector<int>& arr, int l, int m, int r,
               Comparador* cmp)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2)
    {
        if(cmp->comparar(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

void mergeSortPoli(vector<int>& arr, int l, int r,
                   Comparador* cmp)
{
    if(l < r)
    {
        int m = (l + r) / 2;

        mergeSortPoli(arr, l, m, cmp);
        mergeSortPoli(arr, m + 1, r, cmp);

        mergePoli(arr, l, m, r, cmp);
    }
}

// =====================================================
// 4. TEMPLATES
// =====================================================

template <typename T>
struct CLess
{
    bool operator()(T a, T b)
    {
        return a <= b;
    }
};

template <typename T>
struct CGreater
{
    bool operator()(T a, T b)
    {
        return a >= b;
    }
};

template <typename T, typename Cmp>
void mergeTemplate(vector<T>& arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<T> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    Cmp cmp;

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2)
    {
        if(cmp(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

template <typename T, typename Cmp>
void mergeSortTemplate(vector<T>& arr, int l, int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;

        mergeSortTemplate<T, Cmp>(arr, l, m);
        mergeSortTemplate<T, Cmp>(arr, m + 1, r);

        mergeTemplate<T, Cmp>(arr, l, m, r);
    }
}

// =====================================================
// 5. TEMPLATE + INLINE
// =====================================================

template <typename T>
struct InlineLess
{
    inline bool operator()(T a, T b)
    {
        return a <= b;
    }
};

template <typename T, typename Cmp>
inline void mergeInline(vector<T>& arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<T> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    Cmp cmp;

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2)
    {
        if(cmp(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

template <typename T, typename Cmp>
inline void mergeSortInline(vector<T>& arr, int l, int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;

        mergeSortInline<T, Cmp>(arr, l, m);
        mergeSortInline<T, Cmp>(arr, m + 1, r);

        mergeInline<T, Cmp>(arr, l, m, r);
    }
}

// =====================================================
// 6. MACRO
// =====================================================

#define MENOR(a,b) ((a) <= (b))

void mergeMacro(vector<int>& arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2)
    {
        if(MENOR(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

void mergeSortMacro(vector<int>& arr, int l, int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;

        mergeSortMacro(arr, l, m);
        mergeSortMacro(arr, m + 1, r);

        mergeMacro(arr, l, m, r);
    }
}

// =====================================================
// MAIN
// =====================================================

int main()
{
    int n;

    cout << "Ingrese tamaño del array: ";
    cin >> n;

    vector<int> original;

    generarArray(original, n);

    vector<int> a1 = original;
    vector<int> a2 = original;
    vector<int> a3 = original;
    vector<int> a4 = original;
    vector<int> a5 = original;
    vector<int> a6 = original;

    // =========================================
    // NORMAL
    // =========================================

    auto inicio1 = high_resolution_clock::now();

    mergeSortNormal(a1, 0, n - 1);

    auto fin1 = high_resolution_clock::now();

    // =========================================
    // FUNCIONES
    // =========================================

    auto inicio2 = high_resolution_clock::now();

    mergeSortFuncion(a2, 0, n - 1, menorFuncion);

    auto fin2 = high_resolution_clock::now();

    // =========================================
    // POLIMORFISMO
    // =========================================

    Menor cmp;

    auto inicio3 = high_resolution_clock::now();

    mergeSortPoli(a3, 0, n - 1, &cmp);

    auto fin3 = high_resolution_clock::now();

    // =========================================
    // TEMPLATE
    // =========================================

    auto inicio4 = high_resolution_clock::now();

    mergeSortTemplate<int, CLess<int>>(a4, 0, n - 1);

    auto fin4 = high_resolution_clock::now();

    // =========================================
    // TEMPLATE INLINE
    // =========================================

    auto inicio5 = high_resolution_clock::now();

    mergeSortInline<int, InlineLess<int>>(a5, 0, n - 1);

    auto fin5 = high_resolution_clock::now();

    // =========================================
    // MACRO
    // =========================================

    auto inicio6 = high_resolution_clock::now();

    mergeSortMacro(a6, 0, n - 1);

    auto fin6 = high_resolution_clock::now();

    // =========================================
    // RESULTADOS
    // =========================================

    cout << "\n===== TIEMPOS =====\n";

    cout << "Normal: "
         << duration_cast<milliseconds>(fin1 - inicio1).count()
         << " ms\n";

    cout << "Punteros a funciones: "
         << duration_cast<milliseconds>(fin2 - inicio2).count()
         << " ms\n";

    cout << "Polimorfismo: "
         << duration_cast<milliseconds>(fin3 - inicio3).count()
         << " ms\n";

    cout << "Templates: "
         << duration_cast<milliseconds>(fin4 - inicio4).count()
         << " ms\n";

    cout << "Templates inline: "
         << duration_cast<milliseconds>(fin5 - inicio5).count()
         << " ms\n";

    cout << "Macro: "
         << duration_cast<milliseconds>(fin6 - inicio6).count()
         << " ms\n";

    return 0;
}
