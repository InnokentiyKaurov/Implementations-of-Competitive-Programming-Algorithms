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
