const int N = 2e5 + 10, MOD = 1e9 + 7;
 
int inv[N];
int fact[N], inv_fact[N];
 
void precalc(){
  fact[0] = inv_fact[0] = inv[1] = 1;
  for (int i = 2; i < N; i++){
    inv[i] = MOD - (inv[MOD % i] * 1ll * (MOD / i)) % MOD;
  }
  for (int i = 1; i < N; i++){
    fact[i] = (fact[i - 1] * 1ll * i) % MOD;
    inv_fact[i] = (inv_fact[i - 1] * 1ll * inv[i]) % MOD;
  }
}
 
ll ncr(int n, int r){
  return (fact[n] * 1ll * ((inv_fact[r] * 1ll * inv_fact[n - r]) % MOD)) % MOD;
}
