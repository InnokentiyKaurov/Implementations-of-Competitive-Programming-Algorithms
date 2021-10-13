/*
The algorithm finds the maximum matching (by edge count) in explicitly bipartite graph.
I.e. the graph is split into 2 halves of n1 and n2 vertices.
Complexity: O(n1 * m). Usually runs much faster. MUCH FASTER!!!
*/
const int N = 305;

vector<int> g[N]; // Stores edges from left half to right.
bool used[N]; // Stores if vertex from left half is used.
int mt[N]; // For every vertex in right half, stores to which vertex in left half it's matched (-1 if not matched).

bool try_dfs(int v){
  if (used[v]) return false;
  used[v] = 1;
  for (auto u : g[v]){
    if (mt[u] == -1 || try_dfs(mt[u])){
      mt[u] = v;
      return true;
    }
  }
  return false;
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  // cout.precision(20);
  int n1, n2, m;
  cin >> n1 >> n2 >> m;
  while (m--){
    int a, b;
    cin >> a >> b;
    g[a].pb(b);
  }
  for (int i = 1; i <= n2; i++) mt[i] = -1;
  for (int i = 1; i <= n1; i++) used[i] = 0;
  for (int i = 1; i <= n1; i++){
    if (try_dfs(i)){
      for (int j = 1; j <= n1; j++) used[j] = 0;
    }
  }
  vector<pair<int, int>> ans;
  for (int i = 1; i <= n2; i++){
    if (mt[i] != -1) ans.pb({mt[i], i});
  }
  cout << sz(ans) << endl;
  for (auto [a, b] : ans) cout << a << " " << b << endl;
}
