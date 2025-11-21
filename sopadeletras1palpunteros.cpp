#include <iostream>
#include <thread>
using namespace std;

const int N = 10;

int buscarIzqDer(char (*M)[N], const char* WORD, int W) {
    int count = 0;

    for (char (*fila)[N] = M; fila < M + N; fila++) {
        for (int j = 0; j < N; j++) {

            if (j + W <= N) {
                bool ok = true;
                for (int k = 0; k < W; k++) {
                    if ((*fila)[j + k] != WORD[k]) { ok = false; break; }
                }
                if (ok) count++;
            }
        }
    }
    return count;
}

int buscarDerIzq(char (*M)[N], const char* WORD, int W) {
    int count = 0;

    for (char (*fila)[N] = M; fila < M + N; fila++) {
        for (int j = N - 1; j >= 0; j--) {

            if (j - (W - 1) >= 0) {
                bool ok = true;
                for (int k = 0; k < W; k++) {
                    if ((*fila)[j - k] != WORD[k]) { ok = false; break; }
                }
                if (ok) count++;
            }
        }
    }
    return count;
}

int buscarArrAb(char (*M)[N], const char* WORD, int W) {
    int count = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            if (i + W <= N) {
                bool ok = true;
                for (int k = 0; k < W; k++) {
                    if (M[i + k][j] != WORD[k]) { ok = false; break; }
                }
                if (ok) count++;
            }
        }
    }
    return count;
}

int buscarAbArr(char (*M)[N], const char* WORD, int W) {
    int count = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            if (i - (W - 1) >= 0) {
                bool ok = true;
                for (int k = 0; k < W; k++) {
                    if (M[i - k][j] != WORD[k]) { ok = false; break; }
                }
                if (ok) count++;
            }
        }
    }
    return count;
};
int main() {

    const char WORD[] = "ATLETI";
    int W = 6;

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

    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

    thread t1([&]() { c1 = buscarIzqDer(M, WORD, W); });
    thread t2([&]() { c2 = buscarDerIzq(M, WORD, W); });
    thread t3([&]() { c3 = buscarArrAb(M, WORD, W); });
    thread t4([&]() { c4 = buscarAbArr(M, WORD, W); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << "IZQ → DER : " << c1 << "\n";
    cout << "DER → IZQ : " << c2 << "\n";
    cout << "ARR → ABAJO : " << c3 << "\n";
    cout << "ABAJO → ARRIBA : " << c4 << "\n";

    cout << "\nTOTAL ENCONTRADAS: " << (c1 + c2 + c3 + c4) << "\n";

    return 0;
};
