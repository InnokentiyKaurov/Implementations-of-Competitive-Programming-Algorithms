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

const int N = 1e5 + 10;

int n, q;
vector<int> g[N];
int sz[N], dep[N], par[N];
int root[N], pos[N], cnt;

bool comp(int a, int b){
  return sz[a] < sz[b];
}

void dfs1(int v, int p, int d){
  par[v] = p;
  if (p) g[v].erase(find(all(g[v]), p));
  dep[v] = d;
  sz[v] = 1;
  for (auto u : g[v]){
    dfs1(u, v, d + 1);
    sz[v] += sz[u];
  }
  if (!g[v].empty()) iter_swap(g[v].begin(), max_element(all(g[v]), comp));
}

void dfs2(int v, int rt){
  pos[v] = cnt++;
  root[v] = rt;
  for (int i = 0; i < sz(g[v]); i++){
    int u = g[v][i];
    if (!i) dfs2(u, rt);
    else dfs2(u, u);
  }
}

int t[4 * N];
#define lc 2 * v + 1
#define rc lc + 1

void inc(int v, int tl, int tr, int pos, int val){
  if (tl == tr){
    t[v] += val;
    return;
  }
  int tm = (tl + tr) / 2;
  if (pos <= tm) inc(lc, tl, tm, pos, val);
  else inc(rc, tm + 1, tr, pos, val);
  t[v] = max(t[lc], t[rc]);
}

int rmq(int v, int tl, int tr, int l, int r){
  if (l > r) return 0;
  if (tl == l && tr == r){
    return t[v];
  }
  int tm = (tl + tr) / 2;
  return max(
    rmq(lc, tl, tm, l, min(r, tm)),
    rmq(rc, tm + 1, tr, max(l, tm + 1), r)
  );
}

int getans(int u, int v){
  int res = 0;
  for (; root[u] != root[v]; v = par[root[v]]){
    if (dep[root[u]] > dep[root[v]]) swap(u, v);
    res = max(res, rmq(0, 0, n - 1, pos[root[v]], pos[v]));
  }
  if (pos[u] > pos[v]) swap(u, v);
  return max(res, rmq(0, 0, n - 1, pos[u], pos[v]));
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (int i = 1; i < n; i++){
    int a, b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  dfs1(1, 0, 0);
  dfs2(1, 1);
  cin >> q;
  while (q--){
    char c;
    int u, v;
    cin >> c >> u >> v;
    if (c == 'I') inc(0, 0, n - 1, pos[u], v);
    else cout << getans(u, v) << endl;
  }
}
