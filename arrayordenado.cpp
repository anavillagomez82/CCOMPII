#include <iostream>
using namespace std;

// Functor para orden ascendente
template <typename T>
struct Menor {
    bool operator()(const T &a, const T &b) const {
        return a < b;
    }
};

// Functor para orden descendente
template <typename T>
struct Mayor {
    bool operator()(const T &a, const T &b) const {
        return a > b;
    }
};

template <typename T, typename Compare>
class ListaOrdenada {
private:
    T *elementos;
    int capacidad;
    int tam;
    Compare cmp; // compara (asc o desc)

    void redimensionar() {
        int nuevaCapacidad = capacidad > 0 ? capacidad * 2 : 1;
        T *nuevo = new T[nuevaCapacidad];

        for (int i = 0; i < tam; ++i) {
            nuevo[i] = elementos[i];
        }

        delete[] elementos;
        elementos = nuevo;
        capacidad = nuevaCapacidad;
    }

    int posicionInsercion(const T &valor) const {
        int inicio = 0;
        int fin = tam;

        while (inicio < fin) {
            int medio = (inicio + fin) / 2;
            if (cmp(valor, elementos[medio])) {
                fin = medio;
            } else {
                inicio = medio + 1;
            }
        }

        return inicio;
    }

    int buscarIndice(const T &valor) const {
        int inicio = 0;
        int fin = tam - 1;

        while (inicio <= fin) {
            int medio = (inicio + fin) / 2;

            if (elementos[medio] == valor) {
                return medio;
            }

            if (cmp(valor, elementos[medio])) {
                fin = medio - 1;
            } else {
                inicio = medio + 1;
            }
        }

        return -1;
    }

public:
    explicit ListaOrdenada(int capInicial = 10)
        : elementos(new T[capInicial]), capacidad(capInicial), tam(0), cmp(Compare()) {}

    ~ListaOrdenada() {
        delete[] elementos;
    }

    void insertar(const T &valor) {
        if (tam == capacidad) {
            redimensionar();
        }

        int pos = posicionInsercion(valor);

        for (int i = tam; i > pos; --i) {
            elementos[i] = elementos[i - 1];
        }

        elementos[pos] = valor;
        ++tam;
    }

    bool buscar(const T &valor) const {
        return buscarIndice(valor) != -1;
    }

    bool eliminar(const T &valor) {
        int pos = buscarIndice(valor);

        if (pos == -1) {
            return false;
        }

        for (int i = pos; i < tam - 1; ++i) {
            elementos[i] = elementos[i + 1];
        }

        --tam;
        return true;
    }

    void mostrar() const {
        for (int i = 0; i < tam; ++i) {
            cout << elementos[i] << " ";
        }
        cout << "\n";
    }
};

template <typename Compare>
void ejecutarModo() {
    ListaOrdenada<int, Compare> lista;

    int n = 0;
    cout << "Cuantos valores desea insertar? ";
    cin >> n;

    cout << "Ingrese los valores:\n";
    for (int i = 0; i < n; ++i) {
        int x = 0;
        cin >> x;
        lista.insertar(x);
    }

    cout << "Lista ordenada actual: ";
    lista.mostrar();

    int m = 0;
    cout << "Cuantos valores desea eliminar? ";
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int x = 0;
        cout << "Valor a eliminar: ";
        cin >> x;
        if (lista.eliminar(x)) {
            cout << "Eliminado.\n";
        } else {
            cout << "No encontrado.\n";
        }
    }

    cout << "Lista final: ";
    lista.mostrar();
}

int main() {
    int modo = 0;
    cout << "Seleccione el modo de ordenamiento:\n";
    cout << "1. Ascendente\n";
    cout << "2. Descendente\n";
    cout << "Opcion: ";
    cin >> modo;

    if (modo == 1) {
        ejecutarModo<Menor<int>>();
    } else if (modo == 2) {
        ejecutarModo<Mayor<int>>();
    } else {
        std::cout << "Opcion no valida.\n";
    }

    return 0;
}
