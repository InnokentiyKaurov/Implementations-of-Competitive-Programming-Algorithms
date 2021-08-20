/*
Bridges.
Results are stored in a map "is_bridge".
For each connected component, call "dfs(starting vertex, starting vertex)".
*/
const int N = 2e5 + 10; // Careful with the constant!
 
vector<int> g[N];
int tin[N], fup[N], timer;
map<pair<int, int>, bool> is_bridge;
 
void dfs(int v, int p){
  tin[v] = ++timer;
  fup[v] = tin[v];
  for (auto u : g[v]){
    if (!tin[u]){
      dfs(u, v);
      if (fup[u] > tin[v]){
        is_bridge[{u, v}] = is_bridge[{v, u}] = true;
      }
      fup[v] = min(fup[v], fup[u]);
    }
    else{
      if (u != p) fup[v] = min(fup[v], tin[u]);
    }
  }
}



/*
Articulation Points.
Results are stored in an array "is_ap".
For each connected component, call "dfs(starting vertex, starting vertex)".
*/

const int N = 2e5 + 10; // Careful with the constant!
 
vector<int> g[N];
int tin[N], fup[N], timer;
bool is_ap[N];
 
void dfs(int v, int p){
  tin[v] = ++timer;
  fup[v] = tin[v];
  int sons = 0;
  for (auto u : g[v]){
    if (!tin[u]){
      sons++;
      dfs(u, v);
      if (v != p && fup[u] >= tin[v]) is_ap[v] = true;
      fup[v] = min(fup[v], fup[u]);
    }
    else{
      if (u != p) fup[v] = min(fup[v], tin[u]);
    }
  }
  if (v == p && sons > 1) is_ap[v] = true;
}
