#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

// Points

template<typename T>
struct TPoint {
    T x, y;
    int id;

    static constexpr T eps = static_cast<T>(1e-9);

    TPoint() : x(0), y(0), id(-1) {}
    TPoint(const T& x_, const T& y_) : x(x_), y(y_), id(-1) {}
    TPoint(const T& x_, const T& y_, int id_) : x(x_), y(y_), id(id_) {}

    TPoint operator + (const TPoint& rhs) const {
        return TPoint(x + rhs.x, y + rhs.y);
    }

    TPoint operator - (const TPoint& rhs) const {
        return TPoint(x - rhs.x, y - rhs.y);
    }

    TPoint operator * (const T& rhs) const {
        return TPoint(x * rhs, y * rhs);
    }

    TPoint operator / (const T& rhs) const {
        return TPoint(x / rhs, y / rhs);
    }

    bool operator == (const TPoint& rhs) const {
        return abs(x - rhs.x) <= eps && abs(y - rhs.y) <= eps;
    }

    TPoint ort() const {
        return TPoint(-y, x);
    }

    T abs2() const {
        return x * x + y * y;
    }
};

template<typename T>
T smul(const TPoint<T>& a, const TPoint<T>& b) {
    return a.x * b.x + a.y * b.y;
}

template<typename T>
T vmul(const TPoint<T>& a, const TPoint<T>& b) {
    return a.x * b.y - b.x * a.y;
}

template<typename T>
bool ccw(const TPoint<T>& a, const TPoint<T>& b, const TPoint<T>& c) {
    return vmul(b - a, c - a) >= 0;
}

template<typename T>
bool cw(const TPoint<T>& a, const TPoint<T>& b, const TPoint<T>& c) {
    return vmul(b - a, c - a) <= 0;
}

template<typename T>
bool is_zero(const T& a) {
    return abs(a) <= TPoint<T>::eps;
}

// Lines

template<typename T>
struct TLine {
    T a, b, c;

    TLine() : a(0), b(0), c(0) {}
    TLine(const T& a_, const T& b_, const T& c_) : a(a_), b(b_), c(c_) {}
    TLine(const TPoint<T>& p, const TPoint<T>& q) {
        a = q.y - p.y;
        b = p.x - q.x;
        c = -a * p.x - b * p.y;
    }
};

template<typename T>
T det (const T& a11, const T& a12, const T& a21, const T& a22) {
    return a11 * a22 - a12 * a21;
}

template<typename T>
bool parallel(const TLine<T>& l1, const TLine<T>& l2) {
    return is_zero(det(l1.a, l1.b, l2.a, l2.b));
}

template<typename T>
bool equivalent(const TLine<T>& l1, const TLine<T>& l2) {
    return
        parellel(l1, l2) &&
        is_zero(det(l1.c, l1.b, l2.c, l2.b)) &&
        is_zero(det(l1.a, l1.c, l2.a, l2.c));
}

template<typename T>
TPoint<T> intersection(const TLine<T>& l1, const TLine<T>& l2) {
    return TPoint<T>(
        det(l1.c, l1.b, l2.c, l2.b) / det(l1.a, l1.b, l2.a, l2.b),
        det(l1.a, l1.c, l2.a, l2.c) / det(l1.a, l1.b, l2.a, l2.b)
    );
}

// Segments

template<typename T>
int sgn(const T& x) {
    if (is_zero(x)) return 0;
    return x > 0 ? +1 : -1;
}

template<typename T>
bool inter(T a, T b, T c, T d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}

template<typename T>
bool intersects(const TPoint<T>& a, const TPoint<T>& b, const TPoint<T>& c, const TPoint<T>& d) {
    if (is_zero(vmul(b - a, c - a)) && is_zero(vmul(b - a, d - a))) {
        return inter(a.x, b.x, c.x, d.x) && inter(a.y, b.y, c.y, d.y);
    }
    return
        sgn(vmul(b - a, c - a)) != sgn(vmul(b - a, d - a)) &&
        sgn(vmul(d - c, a - c)) != sgn(vmul(d - c, b - c));
}

// Polygons

template<typename T>
ld area(const vector<TPoint<T>>& pts) {
    int n = pts.size();
    T res = 0;
    for (int i = 0; i < n; ++i) {
        res += vmul(pts[i], pts[(i + 1) % n]);
    }
    return abs(res) / 2.0L;
}

template<typename T>
vector<TPoint<T>> convex_hull(vector<TPoint<T>> pts) {
    sort(pts.begin(), pts.end(),
        [] (const TPoint<T>& a, const TPoint<T>& b) {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
        }
    );

    vector<TPoint<T>> hull;
    for (int half = 0; half < 2; ++half) {
        int start = hull.size() + 1;
        for (auto pt : pts) {
            while (hull.size() > start && cw(hull.end()[-2], hull.end()[-1], pt)) {
                hull.pop_back();
            }
            hull.push_back(pt);
        }
        hull.pop_back();
        reverse(pts.begin(), pts.end());
    }
    if (hull.size() == 2 && hull[0] == hull[1]) {
        hull.pop_back();
    }
    return hull;
}

using Point = TPoint<ld>;
using Line = TLine<ld>;

int main() {

}
