vector<int> w(n), c(n), dp(maxW + 1);
  for (int i = 0; i < n; i++){
    for (int j = maxW; j >= w[i]; j--){
      dp[j] = max(dp[j], dp[j - w[i]] + c[i]);
    }
  }
 // *max_element(all(dp)) is the final answer.
