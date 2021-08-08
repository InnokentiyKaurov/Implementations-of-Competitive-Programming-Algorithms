#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
  #define eprint(x) cerr << #x" = " << (x) << endl
  #define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
  #define eprint(x)
  #define eprintf(...)
#endif

#define endl '\n'
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define forn(i, n) for (int i = 0; i < (int) (n); i++)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;
using ld = long double;

const int N = 1e5;

int n, k, a[N], b[N], lazy[N];

void push(int j) {
  if (lazy[j] == -1)
    return;
  for (int i = j * k; i < min(n, (j + 1) * k); i++)
    a[i] = lazy[j];
  lazy[j] = -1;
}

void update(int j) {
  push(j);
  b[j] = INT_MAX;
  for (int i = j * k; i < min(n, (j + 1) * k); i++)
    b[j] = min(b[j], a[i]);
}

void put(int l, int r, int x) {
  push(l / k); push(r / k);
  for (int i = l; i <= r; ) {
    if (i % k == 0 && i + k - 1 <= r) {
      b[i / k] = lazy[i / k] = x;
      i += k;
    } else {
      a[i++] = x;
    }
  }
  update(l / k); update(r / k);
}

int rmq(int l, int r) {
  push(l / k); push(r / k);
  int res = INT_MAX;
  for (int i = l; i <= r; ) {
    if (i % k == 0 && i + k - 1 <= r) {
      res = min(res, b[i / k]);
      i += k;
    } else {
      res = min(res, a[i++]);
    }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  k = sqrt(n) + 1;
  forn(i, n)
    cin >> a[i];
  for (int j = 0; j * k < n; j++) {
    lazy[j] = -1;
    update(j);
  }
  int m;
  cin >> m;
  forn(i, m) {
    int t;
    cin >> t;
    if (t == 1) {
      int l, r;
      cin >> l >> r;
      l--, r--;
      cout << rmq(l, r) << endl;
    } else {
      int l, r, x;
      cin >> l >> r >> x;
      l--, r--;
      put(l, r, x);
    }
  }
}
