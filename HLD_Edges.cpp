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
 
const int N = 1e4 + 10;
 
int n;
vector<pair<int, int>> g[N];
int sz[N], dep[N], par[N];
int root[N], pos[N];
vector<int> a;
vector<pair<int, int>> edges;
 
bool comp(pair<int, int> a, pair<int, int> b){
  return sz[a.fi] < sz[b.fi];
}
 
void dfs1(int v, int p, int d){
  par[v] = p;
  for (auto e : g[v]){
    if (e.fi == p){
      g[v].erase(find(all(g[v]), e));
      break;
    }
  }
  dep[v] = d;
  sz[v] = 1;
  for (auto [u, c] : g[v]){
    dfs1(u, v, d + 1);
    sz[v] += sz[u];
  }
  if (!g[v].empty()) iter_swap(g[v].begin(), max_element(all(g[v]), comp));
}
 
void dfs2(int v, int rt, int c){
  pos[v] = sz(a);
  a.pb(c);
  root[v] = rt;
  for (int i = 0; i < sz(g[v]); i++){
    auto [u, c] = g[v][i];
    if (!i) dfs2(u, rt, c);
    else dfs2(u, u, c);
  }
}
 
int t[4 * N];
#define lc 2 * v + 1
#define rc lc + 1
 
void build(int v, int tl, int tr){
  if (tl == tr){
    t[v] = a[tl];
    return;
  }
  int tm = (tl + tr) / 2;
  build(lc, tl, tm);
  build(rc, tm + 1, tr);
  t[v] = max(t[lc], t[rc]);
}
 
void modify(int v, int tl, int tr, int pos, int val){
  if (tl == tr){
    t[v] = a[tl] = val;
    return;
  }
  int tm = (tl + tr) / 2;
  if (pos <= tm) modify(lc, tl, tm, pos, val);
  else modify(rc, tm + 1, tr, pos, val);
  t[v] = max(t[lc], t[rc]);
}

void modify(int idx, int val){
  modify(0, 0, n - 1, pos[dep[edges[idx].fi] > dep[edges[idx].se]? edges[idx].fi : edges[idx].se], val);
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
  return max(res, rmq(0, 0, n - 1, pos[u] + 1, pos[v]));
}
 
void solve(){
  cin >> n;
  for (int i = 1; i < n; i++){
    int a, b, c;
    cin >> a >> b >> c;
    g[a].pb({b, c});
    g[b].pb({a, c});
    edges.pb({a, b});
  }
  dfs1(1, 0, 0);
  dfs2(1, 1, 0);
  build(0, 0, n - 1);
  while (true){
    string s;
    int a, b;
    cin >> s;
    if (s == "DONE") break;
    cin >> a >> b;
    if (s == "QUERY") cout << getans(a, b) << endl;
    else modify(a - 1, b);
  }
  a.clear();
  for (int i = 0; i < N; i++){
    sz[i] = par[i] = dep[i] = pos[i] = root[i] = t[i] = 0;
    g[i].clear();
  }
  for (int i = 0; i < 4 * N; i++) t[i] = 0;
  edges.clear();
}
 
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--){
    solve();
  }
}
