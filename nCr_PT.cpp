const int N = 1005, MOD = 1e9 + 7;

int ncr[N][N];

void precalc(){
  for (int n = 0; n < N; n++){
    ncr[n][0] = 1;
    for (int r = 1; r <= n; r++){
      ncr[n][r] = (ncr[n - 1][r] + ncr[n - 1][r - 1]) % MOD;
    }
  }
}
