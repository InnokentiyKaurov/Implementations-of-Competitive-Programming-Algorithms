// Euler's totient function computes the number of integers from 1 to n that are co-prime with n.
// Complexity: O(√n).

ll phi(ll n){
  ll ans = n;
  for (ll i = 2; i * i <= n; i++){
    if (n % i) continue;
    while (n % i == 0) n /= i;
    ans -= ans / i;
  }
  if (n > 1) ans -= ans / n;
  return ans;
}


// Precalculates totient function from 1 to N-1.
// Complexity: O(N log log N).

const int N = 2e5 + 20;

int phi[N];

void precalc(){
  for (int i = 0; i < N; i++){
    phi[i] = i;
  }
  for (int i = 2; i < N; i++){
    if (phi[i] == i){
      for (int j = i; j < N; j += i){
        phi[j] -= phi[j] / i;
      }
    }
  }
}
