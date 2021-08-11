// Hash

const int N = 2e5 + 10, P = 31, MOD = 1e9 + 7;

int pw[N];

void precalc(){
  pw[0] = 1;
  for (int i = 1; i < N; i++){
    pw[i] = (pw[i - 1] * 1ll * P) % MOD;
  }
}

struct HT{
  int Hash[N];

  void build(string& s){
    for (int i = 1; i <= sz(s); i++){
      Hash[i] = ((s[i - 1] - 'a' + 1) + P * 1ll * Hash[i - 1]) % MOD;
    }
  }

  int gethash(int l, int r){
    l++, r++;
    int res = (Hash[r] - Hash[l - 1] * 1ll * pw[r - l + 1]) % MOD;
    if (res < 0) res += MOD;
    return res;
  }
};

// Prefix Function, KMP, Prefix Automaton

vector<int> pf(string& s){
  int n = sz(s);
  vector<int> pi(n);
  for (int i = 1; i < n; i++){
    int k = pi[i - 1];
    while (k > 0 && s[i] != s[k]){
      k = pi[k - 1];
    }
    pi[i] = k + (s[i] == s[k]);
  }
  return pi;
}

vector<int> kmp(string& s, string& k){
  string st = k + "#" + s;
  vector<int> res;
  auto pi = pf(st);
  for (int i = 0; i < sz(st); i++){
    if (pi[i] == sz(k)){
      res.pb(i - 2 * sz(k));
    }
  }
  return res;
}

// Converts character to integer value (change depending on situation).
int ctoi(char c){
  return c - 'a';
}

// Sigma is the size of the alphabet.
vector<vector<int>> prefix_automaton(string& s, int sigma){
  int n = sz(s) + 1;
  vector<vector<int>> aut(n, vector<int>(sigma));
  auto pi = pf(s);
  for (int i = 0; i < n; i++){
    for (int j = 0; j < sigma; j++){
      if (ctoi(s[i]) == j) aut[i][j] = i + 1;
      else aut[i][j] = (i? aut[pi[i - 1]][j] : 0);
    }
  }
  return aut;
}

// Z - Function

vector<int> zf(string& s){
  int n = sz(s);
  vector<int> z(n);
  int l = 0, r = 0;
  for (int i = 1; i < n; i++){
    if (r >= i) z[i] = min(z[i - l], r - i + 1);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]){
      z[i]++;
    }
    if (i + z[i] - 1 > r){
      l = i, r = i + z[i] - 1;
    }
  }
  return z;
}

// Trie

const int S = 26;

struct Node{
  vector<int> nxt;
  Node() {
    nxt.assign(S, -1);
  }
};

vector<Node> trie;

void add_str(string& s){
  int v = 0;
  for (auto c : s){
    int cur = c - 'a';
    if (trie[v].nxt[cur] == -1){
      trie[v].nxt[cur] = sz(trie);
      trie.emplace_back();
    }
    v = trie[v].nxt[cur];
  }
}
