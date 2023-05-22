// Trygub numbers: maintaining a large number with a custom base.
// All the digits are stored on the interval (-base, +base).
// Operations:
// 1. Add x * base^y : amortized O(log n * log x / log base). x can be negative.
// 2. Get digit on position k: O (log n). The digit returned is in standard form: [0, +base)
// n is the maximum number of digits.
const int base = 1 << 30;

map<int, ll> dig;

void add(ll x, int y){
  dig[y] += x;
  ll carry;
  do{
    carry = dig[y] / base;
    dig[y] -= carry * base;
    dig[y + 1] += carry;
    if (dig[y] == 0) dig.erase(y);
    y++;
  } while (carry);
  if (dig[y] == 0) dig.erase(y);
}

int get(int k){
  auto iter = dig.lower_bound(k);
  int ans = (iter == dig.end() || iter -> fi != k? 0 : iter -> se);
  if (iter != dig.begin() && prev(iter) -> se < 0) ans--;
  return (ans + base) % base;
}
