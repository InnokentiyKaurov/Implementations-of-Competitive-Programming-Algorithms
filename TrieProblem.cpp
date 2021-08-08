#include <bits/stdc++.h>

using namespace std;

const int LOG = 30;
const int SIGMA = 2;

struct Node {
    vector<int> nxt;
    Node() {
        nxt.assign(SIGMA, -1);
    }
};

vector<Node> trie(1);

void add_number(int x) {
    int v = 0;
    for (int i = LOG; i >= 0; --i) {
        int bit = (x >> i) & 1;
        if (trie[v].nxt[bit] == -1) {
            trie[v].nxt[bit] = trie.size();
            trie.emplace_back();
        }
        v = trie[v].nxt[bit];
    }
}

int max_xor(int x) {
    int res = 0, v = 0;
    for (int i = LOG; i >= 0; --i) {
        int bit = (x >> i) & 1;
        int rbit = bit ^ 1;
        int c = trie[v].nxt[rbit] != -1 ? rbit : bit;
        res += ((bit ^ c) << i);
        v = trie[v].nxt[c];
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (auto x : a) {
        add_number(x);
    }

    int m;
    cin >> m;

    while (m--) {
        int x;
        cin >> x;
        cout << max_xor(x) << endl;
    }
}
