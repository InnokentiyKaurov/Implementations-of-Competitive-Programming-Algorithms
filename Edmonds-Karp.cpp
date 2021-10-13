/*
An algorithm for finding maximum flow in a directed graph.
Complexity: O(N * M ^ 2). Also, no worse than O(M * |F|), where |F| is the value of the maximum flow.
*/

const int N = 105;
const int INF = 1e9 + 20; // Maximum capacity of an edge.

struct edge{
  int from, to, cap, flow;
  edge(int from_, int to_, int cap_, int flow_){
    from = from_, to = to_, cap = cap_, flow = flow_;
  };
};

int n, m; // BE CAREFUL, DON'T REDEFINE N AND M!!!
vector<int> g[N]; // Stores the indices of the outgoing edges for each vertex.
vector<edge> edges; // Stores the edges! To access the reverse edge of idx, use "idx ^ 1".
int par[N]; // Stores the edge index by which each vertex was updated in BFS.

void add_edge(int u, int v, int cap){ // Adds a directed edge from u to v. In undirected graph, call both for (u, v) and (v, u).
  g[u].pb(sz(edges));
  edges.emplace_back(u, v, cap, 0);
  g[v].pb(sz(edges));
  edges.emplace_back(v, u, 0, 0);
}

ll max_flow(int s, int t){
  ll flow = 0;
  while (true){
    for (int i = 1; i <= n; i++) par[i] = -1;
    queue<int> q;
    q.push(s);
    par[s] = 0;
    while (!q.empty()){
      auto v = q.front();
      q.pop();
      for (auto i : g[v]){
        auto [from, to, cap, fl] = edges[i];
        if (par[to] == -1 && cap - fl > 0){
          q.push(to);
          par[to] = i;
        }
      }
    }

    if (par[t] == -1) break;

    int v = t, min_add = INF;
    while (v != s){
      auto cur = edges[par[v]];
      min_add = min(min_add, cur.cap - cur.flow);
      v = cur.from;
    }

    v = t;
    while (v != s){
      int idx = par[v];
      edges[idx].flow += min_add;
      edges[idx ^ 1].flow -= min_add;
      v = edges[idx].from;
    }

    flow += min_add;
  }
  return flow;
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  // cout.precision(20);
  cin >> n >> m;
  while (m--){
    int a, b, c;
    cin >> a >> b >> c;
    add_edge(a, b, c);
    // add_edge(b, a, c); - for an undirected graph
  }
  cout << max_flow(1, n) << endl;
}
