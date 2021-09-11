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

// Eulerian Cycle (Undirected Graphs).
// 1. Graph's edges must be in the same connected component (checked in the algo).
// 2. deg[v] is even for any vertex v (not checked in the algo).
// The algorithm also works for directed graphs.
const int N = 2e5 + 10;

vector<pair<int, int>> g[N];
vector<int> ans;
bool used[N];

void dfs(int v){
  for (auto [u, id] : g[v]){
    if (used[id]) continue;
    used[id] = 1;
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
    g[a].pb({b, i});
    g[b].pb({a, i});
  }
  ans.pb(1);
  dfs(1);
  if (sz(ans) != m){
    // The graph is not connected.
  }
  for (auto i : ans) cout << i << " ";
  cout << endl;
}

// Eulerian Path
// The algo above can be used. Run DFS from one of the terminal vertices (that have odd degree).
// 1. Graph's edges must be in the same connected component (checked in the algo).
// 2. Undirected: Exactly 0 or 2 vertices have odd degree, all other have even degree.
//    Directed: Either all have indeg[x] = outdeg[x],
//              or (one has indeg[v] - outdeg[v] = 1, and one has outdeg[u] - indeg[u] = 1, and all other have indeg[w] = outdeg[w]).
