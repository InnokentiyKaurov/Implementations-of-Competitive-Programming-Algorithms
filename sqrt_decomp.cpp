#include <bits/stdc++.h>

using namespace std;

const int N = 2e5;

int n, a[N], b[N], sz;

void put(int pos, int val) {
    int j = pos / sz;
    a[pos] = val;
    b[j] = INT_MAX;
    for (int i = j * sz; i < min((j + 1) * sz, n); ++i) {
        b[j] = min(b[j], a[i]);
    }
}

int rmq(int l, int r) {
    int ans = INT_MAX;
    for (int i = l; i <= r; ) {
        if (i % sz == 0 && i + sz - 1 <= r) {
            ans = min(ans, b[i / sz]);
            i += sz;
        } else {
            ans = min(ans, a[i++]);
        }
    }
    return ans;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sz = sqrt(n) + 1;
    for (int i = 0; i <= (n - 1) / sz; ++i) {
        b[i] = INT_MAX;
    }
    for (int i = 0; i < n; ++i) {
        b[i / sz] = min(b[i / sz], a[i]);
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int pos, val;
            cin >> pos >> val;
            --pos;
            put(pos, val);
        } else {
            int l, r;
            cin >> l >> r;
            --l, --r;
            cout << rmq(l, r) << endl;
        }
    }
}
