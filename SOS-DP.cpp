// An algorithm for computing the sum of values over all subsets of a set.
// a[MASK] stores the value of the set MASK, and at the end f[MASK] will store the sum of all a[i] such that i is a submask of MASK.
// dp[i][mask] - all bits up to i in submasks MAY differ, but the remaining (n - 1 - i) bits will stay the same.
// Complexity: O(n * 2 ^ n).
// Further reading: https://codeforces.com/blog/entry/45223

// Initialisation:
int a[1 << N], f[1 << N];
int dp[N][1 << N]; // Only needed for Approach #1.

// Approach #1: memory-inefficient, but the history of all results is preserved.
// May be useful for when the values in a[] change on the go.
for (int mask = 0; mask < (1 << n); mask++){
  for (int i = 0; i < n; i++){
    dp[i][mask] = (i? dp[i - 1][mask] : a[mask]) + ((mask >> i) & 1? dp[i][mask ^ (1 << i)] : 0);
  }
  f[mask] = dp[i][mask];
}

// Approach #2: memory-efficient - O(2 ^ n) memory.
// Easy to write, low constant, but the history is not preserved and it can't be used when values in a[] change on the go.
for (int i = 0; i < (1 << n); i++) f[i] = a[i];
for (int i = 0; i < n; i++) for (int mask = 0; mask < (1 << n); mask++) if ((mask >> i) & 1){
  f[mask] += f[mask ^ (1 << i)];
}
