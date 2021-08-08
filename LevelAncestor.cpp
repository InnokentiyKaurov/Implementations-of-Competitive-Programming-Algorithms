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

const int N = 2e5 + 10;

vector<int> g[N];
vector<int> on_dep[N];
int tout[N], timer;
vector<pair<int, int>> v_queries[N], d_queries[N];
vector<int> ans(N, -1);

void dfs(int v, int p, int d){
  on_dep[d].pb(v);
  for (auto u : g[v]){
    if (u != p) dfs(u, v, d + 1);
  }
  tout[v] = timer++;
  for (auto [d, id] : v_queries[v]){
    d_queries[d].pb({v, id});
  }
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, q;
  cin >> n;
  for (int i = 1; i < n; i++){
    int a, b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  cin >> q;
  for (int i = 0; i < q; i++){
    int v, l;
    cin >> v >> l;
    v_queries[v].pb({l, i});
  }
  dfs(1, -1, 0);
  for (int d = 0; d < n; d++){
    for (int i = 0, j = 0; i < sz(on_dep[d]) && j < sz(d_queries[d]);){
      if (tout[on_dep[d][i]] >= tout[d_queries[d][j].fi]){
        ans[d_queries[d][j].se] = on_dep[d][i];
        j++;
      }
      else{
        i++;
      }
    }
  }
  for (int i = 0; i < q; i++) cout << ans[i] << endl;
}
