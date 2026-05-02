#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    int a, b;
    if (!(cin >> a >> b)) return 0;

    if (b <= 1) {
        cout << "infinity" << endl;
        return 0;
    }

    vector<vector<int>> A(a + 1, vector<int>(a + 1, 0));
    for (int n = 1; n <= a; n++) {
        A[n][0] = 1;
        for (int k = 1; k < n; k++) {
            A[n][k] = (n - k) * A[n - 1][k - 1] + (k + 1) * A[n - 1][k];
        }
    }

    int p = 0;
    for (int k = 0; k < a; k++) {
        int term = A[a][k];
        for (int i = 0; i < a - k; i++) term *= b;
        p += term;
    }

    int q = 1;
    for (int i = 0; i < a + 1; i++) q *= (b - 1);

    int common = gcd(p, q);
    cout << p / common << "/" << q / common << endl;

    return 0;
}

