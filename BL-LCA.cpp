const int N = 1e5 + 10, LOG = 20;
 
vector<int> g[N];
 
int par[N][LOG];
int timer, tin[N], tout[N];
 
void dfs(int v, int p){
  par[v][0] = p;
  tin[v] = timer++;
  for (int i = 1; i < LOG; i++) par[v][i] = par[par[v][i - 1]][i - 1];
  for (auto u : g[v]){
    if (u != p) dfs(u, v);
  }
  tout[v] = timer++;
}
 
bool is_anc(int a, int b){
  return tin[a] <= tin[b] && tout[b] <= tout[a];
}
 
int lca(int u, int v){
  if (is_anc(u, v)) return u;
  if (is_anc(v, u)) return v;
  for (int i = LOG - 1; i >= 0; i--){
    if (!is_anc(par[u][i], v)) u = par[u][i];
  }
  return par[u][0];
}
