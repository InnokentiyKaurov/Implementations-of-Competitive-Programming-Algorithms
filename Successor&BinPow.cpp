#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5;
const int kLog = 30;

int f[kMaxN][kLog + 1];

int binPow(int a, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res *= a;
        a *= a;
        k >>= 1;
    }
    return res;
}

int main() {
    int n, q;
    cin >> n >> q;
    for (int v = 0; v < n; ++v) {
        int to;
        cin >> to;
        f[v][0] = --to;
    }

    for (int i = 1; i <= kLog; ++i) {
        for (int v = 0; v < n; ++v) {
            f[v][i] = f[f[v][i - 1]][i - 1];
        }
    }

    while (q--) {
        int v, k;
        cin >> v >> k;
        --v;
        int ans = v;
        for (int i = kLog; i >= 0; --i) {
            int jump = (1 << i);
            if (jump <= k) {
                ans = f[ans][i];
                k -= jump;
            }
        }
        cout << (ans + 1) << endl;
    }
}
