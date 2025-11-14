#include <iostream>
using namespace std;

void SPLIT(int *INI, bool (*CO)(int)) {
    int *p = INI; 
    int* FIN=INI+9;
    for (int *q = INI; q <= FIN; ++q) {
        if (CO(*q)) {
            int temp = *q;
            for (int *s = q; s > p; --s) {
                *s = *(s - 1);
            }
            *p = temp;
            ++p;
        }
    }
}

int main() {
    int A[10] = {1, 2, 3, 7, 10, 11, 25, 30, 32, 40};

    SPLIT(A, [](int a) { return a % 2 == 0; });

    for (int i = 0; i < 10; ++i) cout << A[i] << " ";
    cout << '\n';

    return 0;
};
