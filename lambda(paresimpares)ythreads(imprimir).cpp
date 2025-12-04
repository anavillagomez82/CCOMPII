#include <iostream>
#include <thread>
#include <string>
using namespace std;

template <typename Criterio>
void imprimir(int *arr, int n, Criterio criterio, string nombre) {
    cout << nombre << ": ";
    for (int i = 0; i < n; i++) {
        if (criterio(arr[i])) {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    int a[11] = {15,23,2,3,6,5,72,100,35,8,11};

    auto esPar   = [](int x){ return x % 2 == 0; };
    auto esImpar = [](int x){ return x % 2 != 0; };

    thread t1(imprimir<decltype(esPar)>,   a, 11, esPar,   string("Pares"));
    thread t2(imprimir<decltype(esImpar)>, a, 11, esImpar, string("Impares"));

    t1.join();
    t2.join();

    return 0;
}
