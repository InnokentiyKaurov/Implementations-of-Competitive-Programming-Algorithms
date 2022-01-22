// Divide and Conquer DP Optimization.
// Helps to compute 2D DP of the form dp[i][j] = min(dp[i - 1][k] + cost(k + 1, j)) for each k from 0 to j - 1.
// If k can be j, change FOR loop to "i <= min(mid, optr)".
// However, one condition must hold. Let's say optimal k for state (i, j) is opt(i, j). Then, opt(i, j) <= opt(i, j + 1) must hold for all states.
// Let's say we need to compute dp[M][N]. If the condition above holds, the optimization helps to compute such DP in O(M * N * log N).

// Memory-efficient implementation

vector<ll> dp_old(N), dp_new(N);

void rec(int l, int r, int optl, int optr){
  if (l > r) return;
  int mid = (l + r) / 2;
  pair<ll, int> best = {INF, optl};
  for (int i = optl; i <= min(mid - 1, optr); i++){
    ll cur = dp_old[i] + cost(i + 1, mid);
    if (cur < best.fi) best = {cur, i};
  }
  dp_new[mid] = best.fi;

  rec(l, mid - 1, optl, best.se);
  rec(mid + 1, r, best.se, optr);
}

// Paste in main():
fill(all(dp_old), INF);
dp_old[0] = 0;
while (m--){
   rec(0, n, 0, n);
   dp_old = dp_new;
 }
 cout << dp_new[n] << endl;


// Less memory-efficient implementation

ll dp[M][N];

void rec(int layer, int l, int r, int optl, int optr){
  if (l > r) return;
  int mid = (l + r) / 2;
  int opt = optl;
  for (int i = optl; i <= min(mid - 1, optr); i++){
    ll cur = dp[layer - 1][i] + cost(i + 1, mid);
    if (cur < dp[layer][mid]) dp[layer][mid] = cur, opt = i;
  }
 
  rec(layer, l, mid - 1, optl, opt);
  rec(layer, mid + 1, r, opt, optr);
}

// Paste in main():
memset(dp, 0x3f3f3f3f, sizeof(dp)); // This is the value for infinity. 0x3f3f3f3f ≈ 1e9 + 6e7.
dp[0][0] = 0;
for (int i = 1; i <= m; i++) rec(i, 0, n, 0, n);
cout << dp[m][n] << endl;
