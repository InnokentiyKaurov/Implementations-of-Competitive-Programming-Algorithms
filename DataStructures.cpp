#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define all(arr) (arr).begin(), (arr).end()
#define ll long long
#define ld long double
#define pb push_back
#define sz(x) int((x).size())
#define fi first
#define se second
#define endl '\n'

// USE THESE DATA STRUCTURES GLOBALLY!!!

// DSU
// Clear: makeset()
const int N = 2e5 + 10; // Change the constant!
struct DSU{
  int sz[N], par[N];

  void makeset(int a){
    par[a] = a, sz[a] = 1;
  }

  int getset(int a){
    return par[a] == a? a : par[a] = getset(par[a]);
  }

  bool same(int a, int b){
    return getset(a) == getset(b);
  }

  void unite(int a, int b){
    a = getset(a), b = getset(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a, sz[a] += sz[b];
  }
};

// Sparse Table
// Clear: build()
const int N = 2e5 + 10, LOG = 20; // Change the constant!
template<typename T>
struct SparseTable{
  int lg[N];
  T st[N][LOG];
  int n;

  // Change this function
  function<T(T, T)> f = [&] (T a, T b){
    return min(a, b);
  };

  void build(vector<T>& a){
    n = sz(a);
    lg[1] = 0;
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

    for (int k = 0; k < LOG; k++){
      for (int i = 0; i < n; i++){
        if (!k) st[i][k] = a[i];
        else st[i][k] = f(st[i][k - 1], st[min(n - 1, i + (1 << (k - 1)))][k - 1]);
      }
    }
  }

  T query(int l, int r){
    int sz = r - l + 1;
    return f(st[l][lg[sz]], st[r - (1 << lg[sz]) + 1][lg[sz]]);
  }
};

// Normal SegTree
// Clear: clear() or build()
const int N = 2e5 + 10; // Change the constant!
template<typename T>
struct SegTree{
  T t[4 * N];
  int n;

  // Change this function and default return.
  T default_return = 0;
  function<T(T, T)> f = [&] (T a, T b){
    return a + b;
  };

  SegTree(int n_) : n(n_) {}

  void build(int v, int tl, int tr, vector<T>& a){
    if (tl == tr) {
      t[v] = a[tl];
      return;
    }
    int tm = (tl + tr) / 2;
    // left child: [tl, tm]
    // right child: [tm + 1, tr]
    build(2 * v + 1, tl, tm, a);
    build(2 * v + 2, tm + 1, tr, a);
    t[v] = f(t[2 * v + 1], t[2 * v + 2]);
  }

  SegTree(vector<T>& a){
    build(a);
  }

  void modify(int v, int tl, int tr, int pos, T val){
    if (tl == tr){
      t[v] = val;
      return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm) modify(2 * v + 1, tl, tm, pos, val);
    else modify(2 * v + 2, tm + 1, tr, pos, val);
    t[v] = f(t[2 * v + 1], t[2 * v + 2]);
  }

  T query(int v, int tl, int tr, int l, int r) {
    if (l > r) return default_return;
    if (tl == l && tr == r) return t[v];
    int tm = (tl + tr) / 2;
    return f(
      query(2 * v + 1, tl, tm, l, min(r, tm)),
      query(2 * v + 2, tm + 1, tr, max(l, tm + 1), r)
    );
  }

  void modify(int pos, T val){
    modify(0, 0, n - 1, pos, val);
  }

  T query(int l, int r){
    return query(0, 0, n - 1, l, r);
  }
  
  T get(int pos){
    return query(pos, pos);
  }
  
  // Change clear() function to t.clear() if using unordered_map for SegTree!!!
  void clear(int n_){
    n = n_;
    for (int i = 0; i < 4 * n; i++) t[i] = 0;
  }

  void build(vector<T>& a){
    n = sz(a);
    clear(n);
    build(0, 0, n - 1, a);
  }
};

// Lazy Propagation SegTree
// Clear: clear() or build()
const int N = 2e5 + 10; // Change the constant!
template<typename T>
struct LazySegTree{
  T t[4 * N];
  T lazy[4 * N];
  int n;

  // Change these functions, default return, and lazy mark.
  T default_return = 0, lazy_mark = numeric_limits<T>::min();
  // Lazy mark is how the algorithm will identify that no propagation is needed.
  function<T(T, T)> f = [&] (T a, T b){
    return a + b;
  };
  // f_on_seg calculates the function f, knowing the lazy value on segment,
  // segment's size and the previous value.
  // The default is segment modification for RSQ. For increments change to:
  //     return cur_seg_val + seg_size * lazy_val;
  // For RMQ.   Modification: return lazy_val;   Increments: return cur_seg_val + lazy_val;
  function<T(T, int, T)> f_on_seg = [&] (T cur_seg_val, int seg_size, T lazy_val){
    return seg_size * lazy_val;
  };
  // upd_lazy updates the value to be propagated to child segments.
  // Default: modification. For increments change to:
  //     lazy[v] = (lazy[v] == lazy_mark? val : lazy[v] + val);
  function<void(int, T)> upd_lazy = [&] (int v, T val){
    lazy[v] = val;
  };
  // Tip: for "get element on single index" queries, use max() on segment: no overflows.

  LazySegTree(int n_) : n(n_) {
    clear(n);
  }

  void build(int v, int tl, int tr, vector<T>& a){
    if (tl == tr) {
      t[v] = a[tl];
      return;
    }
    int tm = (tl + tr) / 2;
    // left child: [tl, tm]
    // right child: [tm + 1, tr]
    build(2 * v + 1, tl, tm, a);
    build(2 * v + 2, tm + 1, tr, a);
    t[v] = f(t[2 * v + 1], t[2 * v + 2]);
  }

  LazySegTree(vector<T>& a){
    build(a);
  }

  void push(int v, int tl, int tr){
    if (lazy[v] == lazy_mark) return;
    int tm = (tl + tr) / 2;
    t[2 * v + 1] = f_on_seg(t[2 * v + 1], tm - tl + 1, lazy[v]);
    t[2 * v + 2] = f_on_seg(t[2 * v + 2], tr - tm, lazy[v]);
    upd_lazy(2 * v + 1, lazy[v]), upd_lazy(2 * v + 2, lazy[v]);
    lazy[v] = lazy_mark;
  }
  
  void modify(int v, int tl, int tr, int l, int r, T val){
    if (l > r) return;
    if (tl == l && tr == r){
      t[v] = f_on_seg(t[v], tr - tl + 1, val);
      upd_lazy(v, val);
      return;
    }
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    modify(2 * v + 1, tl, tm, l, min(r, tm), val);
    modify(2 * v + 2, tm + 1, tr, max(l, tm + 1), r, val);
    t[v] = f(t[2 * v + 1], t[2 * v + 2]);
  }
  
  T query(int v, int tl, int tr, int l, int r) {
    if (l > r) return default_return;
    if (tl == l && tr == r) return t[v];
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    return f(
      query(2 * v + 1, tl, tm, l, min(r, tm)),
      query(2 * v + 2, tm + 1, tr, max(l, tm + 1), r)
    );
  }
  
  void modify(int l, int r, T val){
    modify(0, 0, n - 1, l, r, val);
  }

  T query(int l, int r){
    return query(0, 0, n - 1, l, r);
  }
  
  T get(int pos){
    return query(pos, pos);
  }
  
  // Change clear() function to t.clear() if using unordered_map for SegTree!!!
  void clear(int n_){
    n = n_;
    for (int i = 0; i < 4 * n; i++) t[i] = 0, lazy[i] = lazy_mark;
  }

  void build(vector<T>& a){
    n = sz(a);
    clear(n);
    build(0, 0, n - 1, a);
  }
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  // cout.precision(20);
  
}
