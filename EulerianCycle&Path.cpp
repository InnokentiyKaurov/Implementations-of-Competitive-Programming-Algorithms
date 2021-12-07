// IT'S ALSO IMPORTANT THAT THE STARTING VERTEX IS NOT ISOLATED. So sz(g[start]) > 0.

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
  while (!g[v].empty()){
    auto [u, id] = g[v].back();
    g[v].pop_back();
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
  ans.pb(1); // For Eulerian Path, change to ans.pb(finish);
  dfs(1); // For Eulerian Path, change to dfs(start);
  if (sz(ans) != m){
    // The graph is not connected.
  }
  for (auto i : ans) cout << i << " ";
  cout << endl;
}

// Eulerian Path
// The algo above can be used. Run DFS from one of the terminal vertices (that have odd degree). Don't forget to change line 69!
// 1. Graph's edges must be in the same connected component (checked in the algo).
// 2. Undirected: Exactly 0 or 2 vertices have odd degree, all other have even degree.
//    Directed: Either all have indeg[x] = outdeg[x],
//              or (one has indeg[v] - outdeg[v] = 1, and one has outdeg[u] - indeg[u] = 1, and all other have indeg[w] = outdeg[w]).

// Set-up for Eulerian Path in undirected graph:
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
  int st = -1, fin = -1;
  for (int i = 1; i <= n; i++){
    if (sz(g[i]) & 1){
      if (st == -1) st = i;
      else if (fin == -1) fin = i;
      else{
        cout << "NO" << endl;
        return 0;
      }
    }
  }
  if (st != -1 && fin == -1){
    cout << "NO" << endl;
    return 0;
  }
  if (st == -1) st = fin = 1;
  ans.pb(fin); // Pay attention to these lines!!!
  dfs(st); // Pay attention to these lines!!!
  if (sz(ans) - 1 != m){
    cout << "NO" << endl;
  }
  else{
    cout << "YES" << endl;
    for (auto i : ans) cout << i << " ";
    cout << endl;
  }
}
