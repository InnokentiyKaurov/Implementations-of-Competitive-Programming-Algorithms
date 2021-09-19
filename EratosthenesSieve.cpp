// Standard Prime-Searching Sieve: O(n log log n).
const int N = 1e6 + 20;

vector<bool> is_prime(N, 1);

void precalc(){
  is_prime[0] = is_prime[1] = 0;
  for (int i = 2; i * i < N; i++){
    if (is_prime[i]){
      for (int j = i * i; j < N; j += i){
        is_prime[j] = 0;
      }
    }
  }
}

// Sieve for fast prime factorisation. Precalc: O(n log log n). Query: O(log n).
// lpf[x] stores the lowest prime factor of x.
const int N = 1e6 + 20;

vector<bool> is_prime(N, 1);
int lpf[N];

void precalc(){
  is_prime[0] = is_prime[1] = 0;
  for (int i = 2; i < N; i++){
    if (is_prime[i]){
      lpf[i] = i;
      for (ll j = i * 1ll * i; j < N; j += i){
        is_prime[j] = 0;
        if (!lpf[j]) lpf[j] = i;
      }
    }
  }
}

vector<pair<int, int>> factorise(int x){
  vector<pair<int, int>> ret;
  while (x > 1){
    int c = 0;
    int f = lpf[x];
    while (lpf[x] == f){
      x /= f;
      c++;
    }
    ret.pb({f, c});
  }
  return ret;
}
