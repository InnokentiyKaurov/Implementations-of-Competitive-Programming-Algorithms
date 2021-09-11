// Eulerian Cycle (Directed Graphs).
// 1. Graph's edges must be in the same connected component (checked in the algo).
// 2. indeg[v] = outdeg[v] for any vertex v (not checked in the algo).
const int N = 2e5 + 10;

vector<int> g[N], ans;

void dfs(int v){
  while (!g[v].empty()){
    int u = g[v].back();
    g[v].pop_back();
    dfs(u);
    ans.pb(v);
  }
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  // cout.precision(20);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++){
    int a, b;
    cin >> a >> b;
    g[a].pb(b);
  }
  dfs(1);
  reverse(all(ans));
  if (sz(ans) != m){
    // The graph is not connected.
  }  
  ans.pb(1);
  for (auto i : ans) cout << i << " ";
  cout << endl;
}

