#include <bits/stdc++.h>

using namespace std;

double sq(double x) {
    return x * x;
}

double dist(double x1, double y1, double x2, double y2) {
    return sqrt(sq(x1 - x2) + sq(y1 - y2));
}

int main() {
    int n, m, A, B;
    cin >> n >> m >> A >> B;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    vector<int> c(m);
    for (int i = 0; i < m; ++i) {
        cin >> c[i];
    }

    auto f = [&] (int i, int j) {
        return dist(0, 0, A, a[i]) + dist(A, a[i], B, b[j]) + c[j];
    };

    double ans_val = DBL_MAX;
    int ans_i = -1, ans_j = -1;
    for (int j = 0; j < m; ++j) {
        int l = 0, r = n;
        while (r - l >= 3) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;
            if (f(m1, j) < f(m2, j)) {
                r = m2;
            } else {
                l = m1;
            }
        }
        for (int i = l; i <= r; ++i) {
            double cur_val = f(i, j);
            if (cur_val < ans_val) {
                ans_val = cur_val;
                ans_i = i, ans_j = j;
            }
        }
    }

    cout << (ans_i + 1) << " " << (ans_j + 1) << endl;
}
