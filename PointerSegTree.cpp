#define _USE_MATH_DEFINES

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
#define sz(x) int((x).size())
#define all(x) (x).begin(), (x).end()
#define forn(i, n) for (int i = 0; i < int(n); i++)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;
using ld = long double;

struct Node {
  int val;
  Node *l, *r;
  Node() : val(0), l(nullptr), r(nullptr) {}
};

int getVal(Node *t) {
  return t ? t->val : 0;
}

Node* modify(Node *t, int tl, int tr, int pos, int x) {
  if (!t)
    t = new Node();
  else
    t = new Node(*t);
  if (tl == tr) {
    t->val = x;
    return t;
  }
  int tm = (tl + tr) / 2;
  if (pos <= tm)
    t->l = modify(t->l, tl, tm, pos, x);
  else
    t->r = modify(t->r, tm + 1, tr, pos, x);
  t->val = getVal(t->l) + getVal(t->r);
  return t;
}

int lowerBound(Node *t, int tl, int tr, int k) {
  if (tl == tr)
    return tl;
  int tm = (tl + tr) / 2;
  if (k <= getVal(t->l))
    return lowerBound(t->l, tl, tm, k);
  else
    return lowerBound(t->r, tm + 1, tr, k - getVal(t->l));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n;
  cin >> n;
  vector<int> a(n);
  forn(i, n) {
    cin >> a[i];
    a[i]--;
  }
  vector<Node*> st(n + 1);
  st[n] = modify(nullptr, 0, n, n, 1);
  vector<int> prv(n, -1);
  for (int i = n - 1; i >= 0; i--) {
    Node *cur = st[i + 1];
    if (prv[a[i]] != -1)
      cur = modify(cur, 0, n, prv[a[i]], 0);
    st[i] = modify(cur, 0, n, i, 1);
    prv[a[i]] = i;
  }
  for (int k = 1; k <= n; k++) {
    int ans = 0, pos = 0;
    while (pos < n) {
      pos = lowerBound(st[pos], 0, n, k + 1);
      ans++;
    }
    cout << ans << ' ';
  }
  cout << endl;
}
