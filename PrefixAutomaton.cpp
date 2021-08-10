#include <bits/stdc++.h>
using namespace std;

const int SIGMA = 26;
const int N = 101;

int dp[N][N][N], prv[N][N][N];

vector<int> prefix_function(string s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[j] != s[i])
            j = pi[j - 1];
        pi[i] = j + (s[j] == s[i]);
    }
    return pi;
}

vector<vector<int>> prefx_automaton(string s) {
    int n = s.size() + 1;
    auto pi = prefix_function(s);
    vector<vector<int>> aut(n, vector<int>(SIGMA));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < SIGMA; j++) {
            if (s[i] == ('A' + j))
                aut[i][j] = i + 1;
            else if (i > 0)
                aut[i][j] = aut[pi[i - 1]][j];
        }
    return aut;
}

int main() {
    string s, t, p;
    cin >> s >> t >> p;
    int n = s.size(), m = t.size(), r = p.size();
    auto aut = prefx_automaton(p);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k < r; k++) {
                if (i + 1 <= n && dp[i + 1][j][k] <= dp[i][j][k]) {
                    dp[i + 1][j][k] = dp[i][j][k];
                    prv[i + 1][j][k] = -2;
                }
                if (j + 1 <= m && dp[i][j + 1][k] <= dp[i][j][k]) {
                    dp[i][j + 1][k] = dp[i][j][k];
                    prv[i][j + 1][k] = -1;
                }
                if (i + 1 <= n && j + 1 <= m && s[i] == t[j]) {
                    int l = aut[k][s[i] - 'A'];
                    if (dp[i + 1][j + 1][l] <= dp[i][j][k] + 1) {
                        dp[i + 1][j + 1][l] = dp[i][j][k] + 1;
                        prv[i + 1][j + 1][l] = k;
                    }
                }
            }
    string ans;
    int k = 0;
    for (int i = 0; i < r; i++)
        if (dp[n][m][i] > dp[n][m][k])
            k = i;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        int val = prv[i][j][k];
        if (val == -2)
            i--;
        else if (val == -1)
            j--;
        else {
            i--, j--;
            k = val;
            ans += s[i];
        }
    }
    reverse(ans.begin(), ans.end());
    if (ans.empty())
        cout << 0 << endl;
    else
        cout << ans << endl;
}
