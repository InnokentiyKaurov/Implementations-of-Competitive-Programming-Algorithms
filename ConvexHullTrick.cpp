// Convex Hull Trick. Allows to insert a linear function to the hull in Ө(1) and get the minimum/maximum value of the stored function at a point in O(log n).
// NOTE: The lines must be added in the order of decreasing/increasing gradients. CAREFULLY CHECK THE SETUP BEFORE USING!
struct line{
  ll k, b;
  ll f(ll x){
    return k * x + b;
  };
};
 
vector<line> hull;
 
void add_line(line nl){
  if (!hull.empty() && hull.back().k == nl.k){
    nl.b = min(nl.b, hull.back().b); // Default: minimum. For maximum change "min" to "max".
    hull.pop_back();
  }
  while (sz(hull) > 1){
    auto& l1 = hull.end()[-2], l2 = hull.back();
    if ((nl.b - l1.b) * (l2.k - nl.k) >= (nl.b - l2.b) * (l1.k - nl.k)) hull.pop_back(); // Default: decreasing gradient k. For increasing k change the sign to <=.
    else break;
  }
  hull.pb(nl);
}
 
ll get(ll x){
  int l = 0, r = sz(hull);
  while (r - l > 1){
    int mid = (l + r) / 2;
    if (hull[mid - 1].f(x) >= hull[mid].f(x)) l = mid; // Default: minimum. For maximum change the sign to <=.
    else r = mid;
  }
  return hull[l].f(x);
}
