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

const int N = 1e5 + 10, INF = 2e9;

vector<pair<int, int>> g[N];
vector<ll> dist(N, INF);

signed main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  // cout.precision(20);
  int n, m;
  cin >> n >> m;
  while (m--){
    int a, b, w;
    cin >> a >> b >> w;
    a--, b--;
    g[a].pb({b, w});
    g[b].pb({a, w});
  }
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
  dist[0] = 0;
  q.push({0, 0});
  while (!q.empty()){
    auto [d, v] = q.top();
    q.pop();
    if (d != dist[v]) continue;
    for (auto [u, w] : g[v]){
      if (dist[u] > dist[v] + w){
        dist[u] = dist[v] + w;
        q.push({dist[u], u});
      }
    }
  }
  for (int i = 0 ; i < n; i++){
    cout << dist[i] << " ";
  }
  cout << endl;
}
