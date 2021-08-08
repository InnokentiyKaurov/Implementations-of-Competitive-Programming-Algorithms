#pragma GCC optimize("O3")
#pragma GCC target ("avx2")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>

using namespace std;

const int N = 100;

double IT = 70;
double L = -1e4, R = +1e4;

int n;
double px[N], py[N], pz[N], tx, ty, tz;

double sq(double x) {
    return x * x;
}

double dist(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sq(x1 - x2) + sq(y1 - y2) + sq(z1 - z2);
}

double f(double x, double y, double z) {
    double res = 0;
    for (int i = 0; i < n; ++i) {
        res = max(res, dist(x, y, z, px[i], py[i], pz[i]));
    }
    return res;
}

double f_xy(double x, double y) {
    double l = L, r = R;
    for (int i = 0; i < IT; ++i) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(x, y, m1) <= f(x, y, m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    tz = l;
    return f(x, y, l);
}

double f_x(double x) {
    double l = L, r = R;
    for (int i = 0; i < IT; ++i) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f_xy(x, m1) <= f_xy(x, m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    ty = l;
    return f_xy(x, l);
}

double f_() {
    double l = L, r = R;
    for (int i = 0; i < IT; ++i) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f_x(m1) <= f_x(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    tx = l;
    return f_x(l);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> px[i] >> py[i] >> pz[i];
    }

    f_();

    cout << setprecision(10) << fixed;
    cout << tx << " " << ty << " " << tz << endl;
}
