#include <bits/stdc++.h>
using namespace std;
#define all(arr) (arr).begin(), (arr).end()
#define ll long long
#define pb push_back
#define sz(x) int((x).size())
#define fi first
#define se second
#define endl '\n'

/*
Ordered Set

Main Functions:
order_of_key(k) - returns index of k.
*find_by_order(k) - returns k-th element.

Remarks:
No function "count": instead use "set.find(k) == set.end()".
All other main set functions are present.
Multiset doesn't have normal erase() function. You have to write:
    set.erase(set.find_by_order(set.order_of_key(x)));
*/

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ordered_set oset;
  int q;
  cin >> q;
  while (q--){
    string s;
    int x;
    cin >> s >> x;
    if (s == "ADD"){
      if (oset.find(x) == oset.end()){
        cout << "YES" << endl;
      }
      else{
        cout << "NO" << endl;
      }
      oset.insert(x);
    }
    if (s == "REMOVE"){
      if (oset.find(x) == oset.end()){
        cout << "NO" << endl;
      }
      else{
        cout << "YES" << endl;
      }
      oset.erase(x);
    }
    if (s == "FIND"){
      if (oset.find(x) == oset.end()){
        cout << -1 << endl;
      }
      else{
        cout << oset.order_of_key(x) + 1 << endl;
      }
    }
  }
}
