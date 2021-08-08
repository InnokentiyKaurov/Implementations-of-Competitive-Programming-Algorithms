#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define all(arr) (arr).begin(), (arr).end()
#define ll long long
#define ld long double
#define pb push_back
#define sz(x) int((x).size())
#define fi first
#define se second
#define endl '\n'

const int MOD = 1e9 + 7;

template<typename T = ll>
struct Matrix{
  vector<vector<T>> m;
  int n;
  
  Matrix() : n(0){}

  Matrix(int N_){
    n = N_;
    m = vector<vector<T>>(n, vector<T>(n));
  }
  
  Matrix(int N_, T val){
    n = N_;
    m = vector<vector<T>>(n, vector<T>(n));
    for (int i = 0; i < n; i++) m[i][i] = val;
  }
  
  Matrix<T> operator* (Matrix<T>& rhs){
    Matrix<T> res(n);
    for (int i = 0; i < n; i++){
      for (int j = 0; j < n; j++){
        for (int k = 0; k < n; k++){
          res.m[i][j] = (res.m[i][j] + m[i][k] * 1ll * rhs.m[k][j]) % MOD;
        }
      }
    }
    return res;
  }
};

template<typename T = ll, typename X = ll>
Matrix<T> matpow(Matrix<T>& a, X b){
  Matrix<T> res = Matrix<T>(a.n, 1);
  for (Matrix<T> cur = a; b; cur = cur * cur, b >>= 1ll){
    if (b & 1ll) res = res * cur;
  }
  return res;
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  // cout.precision(20);
  
}