#include <bits/stdc++.h>
using namespace std;
#define all(arr) (arr).begin(), (arr).end()
#define ll long long
#define pb push_back
#define sz(x) int((x).size())
#define fi first
#define se second
#define endl '\n'

const int N = 6e5 + 10, LOG = 23;

vector<int> g[N], euler;
int depth[N], occ[N], lg[N];
pair<int, int> st[N][LOG];

void dfs(int v, int p, int d){
  occ[v] = sz(euler);
  euler.pb(v);
  depth[v] = d;
  for (auto u : g[v]){
    if (u != p){
      dfs(u, v, d + 1);
      euler.pb(v);
    }
  }
}

void precalc(){
  for (int i = 2; i < N; i++) lg[i] = lg[i / 2] + 1;
}

void build(){
  dfs(0, 0, 0);
  int n = sz(euler);
  for (int i = 0; i < n; i++) st[i][0] = {depth[euler[i]], euler[i]};
  for (int k = 1; k < LOG; k++){
    for (int i = 0; i + (1 << k) <= n; i++){
      st[i][k] = min(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
    }
  }
  precalc();
}

int lca(int a, int b){
  a = occ[a], b = occ[b];
  if (a > b) swap(a, b);
  int lgsz = lg[b - a + 1];
  return min(st[a][lgsz], st[b - (1 << lgsz) + 1][lgsz]).se;
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
}
