struct SuffixArray{
  vector<int> p, c, h;
  /*
  In the end, array c gives the position of each suffix in p
  using 1-based indexation!
  */

  SuffixArray() {}

  SuffixArray(string s){
    buildArray(s);
    buildLCP(s);
  }

  void buildArray(string s){
    int n = sz(s) + 1;
    p.resize(n), c.resize(n);
    for (int i = 0; i < n; i++) p[i] = i;

    // Sort & classify single characters.
    sort(all(p), [&] (int a, int b){return s[a] < s[b];});
    c[p[0]] = 0;
    for (int i = 1; i < n; i++){
      c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
    }

    vector<int> p2(n), c2(n);
    // w is half-length of each string.
    for (int w = 1; w < n; w <<= 1){
      // Sort by second half.
      for (int i = 0; i < n; i++){
        p2[i] = (p[i] - w + n) % n;
      }

      // Count-sort by first half.
      vector<int> cnt(n);
      for (auto i : c) cnt[i]++;
      for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
      for (int i = n - 1; i >= 0; i--){
        p[--cnt[c[p2[i]]]] = p2[i];
      }

      // Classify.
      c2[p[0]] = 0;
      for (int i = 1; i < n; i++){
        c2[p[i]] = c2[p[i - 1]] + 
        (c[p[i]] != c[p[i - 1]] ||
        c[(p[i] + w) % n] != c[(p[i - 1] + w) % n]);
      }
      c.swap(c2);
    }
    p.erase(p.begin());
  }

  void buildLCP(string s){
    // The algorithm assumes that suffix array is already built on the same string.
    int n = sz(s);
    h.resize(n - 1);
    int k = 0;
    for (int i = 0; i < n; i++){
      if (c[i] == n){
        k = 0;
        continue;
      }
      int j = p[c[i]];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
      h[c[i] - 1] = k;
      if (k) k--;
    }
    /*
    Then an RMQ Sparse Table can be built on array h
    to calculate LCP of 2 non-consecutive suffixes.
    */
  }
};
