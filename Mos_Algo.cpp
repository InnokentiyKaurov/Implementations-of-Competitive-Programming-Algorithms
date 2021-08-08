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

struct query {
  static const int bucketSize = 500;
  int l, r, id;
  
  pair<int, int> toPair() {
    return {l / bucketSize, ((l / bucketSize) & 1) ? -r : +r};
  }
  
  friend bool operator< (query &a, query &b) {
    return a.toPair() < b.toPair();
  }
};

unordered_map<int, int> cnt;
int diffCnt;

void add(int x) {
  if (cnt[x]++ == 0)
    diffCnt++;
}

void remove(int x) {
  if (cnt[x]-- == 1)
    diffCnt--;
}

int eval() {
  return diffCnt;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  forn(i, n)
    cin >> a[i];
  vector<query> queries;
  forn(i, m) {
    int l, r;
    cin >> l >> r;
    queries.push_back({l, r, i});
  }
  sort(all(queries));
  vector<int> ans(m);
  int L = 0, R = -1;
  for (auto q : queries) {
    int l = q.l, r = q.r, id = q.id;
    while (l < L) add(a[--L]);
    while (R < r) add(a[++R]);
    while (L < l) remove(a[L++]);
    while (r < R) remove(a[R--]);
    ans[id] = eval();
  }
  for (auto x : ans)
    cout << x << endl;
 }
