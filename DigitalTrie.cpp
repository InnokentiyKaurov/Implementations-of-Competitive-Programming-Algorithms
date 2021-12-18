const int S = 2, LOG = 30;

bool bit(int x, int i){
  return (x >> i) & 1;
}

struct Node{
  vector<int> nxt;
  Node() {
    nxt.assign(S, -1);
  }
};

vector<Node> trie(1);

void add_num(int x){
  int v = 0;
  for (int i = LOG - 1; i >= 0; i--){
    int cur = bit(x, i);
    if (trie[v].nxt[cur] == -1){
      trie[v].nxt[cur] = sz(trie);
      trie.emplace_back();
    }
    v = trie[v].nxt[cur];
  }
}
