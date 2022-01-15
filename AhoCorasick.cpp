const int S = 26;

// Function converting char to int.
int ctoi(char c){
  return c - 'a';
}

struct Node{
  vector<int> nxt;
  int link;
  bool terminal;

  Node() {
    nxt.assign(S, -1), link = 0, terminal = 0;
  }
};

vector<Node> trie(1);

// add_str returns the terminal vertex.
int add_str(string& s){
  int v = 0;
  for (auto c : s){
    int cur = ctoi(c);
    if (trie[v].nxt[cur] == -1){
      trie[v].nxt[cur] = sz(trie);
      trie.emplace_back();
    }
    v = trie[v].nxt[cur];
  }
  trie[v].terminal = 1;
  return v;
}

/*
Suffix links are compressed.
This means that:
  If vertex v has a child by letter x, then:
    trie[v].nxt[x] points to that child.
  If vertex v doesn't have such child, then:
    trie[v].nxt[x] points to the suffix link of that child
    if we would actually have it.
*/
void add_links(){
  queue<int> q;
  q.push(0);
  while (!q.empty()){
    auto v = q.front();
    int u = trie[v].link;
    q.pop();
    for (int i = 0; i < S; i++){
      int& ch = trie[v].nxt[i];
      if (ch == -1){
        ch = v? trie[u].nxt[i] : 0;
      }
      else{
        trie[ch].link = v? trie[u].nxt[i] : 0;
        q.push(ch);
      }
    }
  }
}
