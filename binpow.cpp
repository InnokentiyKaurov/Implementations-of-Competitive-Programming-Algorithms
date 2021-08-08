const int MOD = 1e9 + 7;

int binpow(int a, int b){
  ll res = 1;
  for (; b; a = (a * 1ll * a) % MOD, b >>= 1){
    if (b & 1) res = (res * a) % MOD;
  }
  return res;
}

int inv(int a){
  return binpow(a, MOD - 2);
}
