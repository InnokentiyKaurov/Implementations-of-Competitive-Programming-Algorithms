#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define all(arr) (arr).begin(), (arr).end()
#define ll long long
#define pb push_back
#define sz(x) int((x).size())
#define fi first
#define se second
#define endl '\n'

const int N = 2e5 + 10;

int sz[N], par[N];

void makeset(int a){
  sz[a] = 1, par[a] = a;
}

int getset(int a){
  return par[a] == a? a : par[a] = getset(par[a]);
}

void unite(int a, int b){
  a = getset(a), b = getset(b);
  if (sz[a] < sz[b]) swap(a, b);
  sz[a] += sz[b];
  par[b] = a;
}

vector<int> g[N];
vector<pair<int, int>> queries[N];
int root[N], lca[N];

void dfs(int v){
  makeset(v);
  root[v] = v;
  for (auto u : g[v]){
    if (!sz[u]){
      dfs(u);
      unite(u, v);
      root[getset(v)] = v;
    }
  }
  for (auto [u, id] : queries[v]){
    if (!sz[u]) continue;
    lca[id] = root[getset(u)];
  }
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
}
