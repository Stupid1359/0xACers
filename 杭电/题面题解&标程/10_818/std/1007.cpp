#include <bits/stdc++.h>

#define rep(i, j, k) for (int i = (j); i <= (k); ++i)
#define per(i, j, k) for (int i = (j); i >= (k); --i)
#define SZ(v) int((v).size())
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
using ll = long long;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;

template<class T> void chkmn(T &x, T y) { if (y < x) x = y; }
template<class T> void chkmx(T &x, T y) { if (y > x) x = y; }

using namespace std;

const int maxn = 200010;

int n, q, lim, a[maxn], sum[maxn];
double inv[maxn];
string str;
set<pii> S;

void add(int len) {
  rep (i, 0, lim) sum[i] += int(len * inv[i]);
}

void del(int len) {
  rep (i, 0, lim) sum[i] -= int(len * inv[i]);
}

void split(int x) {
  auto it = S.lower_bound(pii(x + 1, 0));
  if (it == S.begin()) return;
  it = prev(it);
  if (it -> se <= x) return;
  auto [l, r] = *it;
  S.erase(it), del(r - l + 1);
  S.insert(pii(l, x)), add(x - l + 1);
  S.insert(pii(x + 1, r)), add(r - x);
}

void work() {
  cin >> n >> q >> str, S.clear(), lim = n;
  rep (i, 0, n) chkmn(lim, i + (n + 2 * i) / (2 * i + 1));
  rep (i, 0, lim) sum[i] = 0, inv[i] = 1. / (2 * i + 1) + 1e-9;
  rep (i, 1, n) a[i] = str[i - 1] - '0';
  for (int l = 1, r; l <= n; l = r + 1) {
    r = l;
    while (r < n && a[r + 1] == a[l]) r++;
    if (!a[l]) add(r - l + 1), S.insert(pii(l, r));
  }
  rep (i, 1, q) {
    int op, l, r;
    cin >> op >> l >> r;
    split(l - 1), split(r);
    auto itl = S.lower_bound(pii(l, 0));
    auto itr = itl;
    while (itr != S.end() && (itr -> se) <= r) del((itr -> se) - (itr -> fi) + 1), itr++;
    S.erase(itl, itr);
    if (op == 2) {
      int cl = l, cr = r;
      auto it = S.lower_bound(pii(l + 1, 0));
      if (it != S.begin() && prev(it) -> se == l - 1) {
        it = prev(it), del((it -> se) - (it -> fi) + 1);
        cl = it -> fi, S.erase(it);
      }
      it = S.lower_bound(pii(r + 1, 0));
      if (it != S.end() && it -> fi == r + 1) {
        del((it -> se) - (it -> fi) + 1);
        cr = it -> se, S.erase(it);
      }
      S.insert(pii(cl, cr)), add(cr - cl + 1);
    }
    if (S.empty()) {
      cout << "0\n";
      continue;
    }
    if (SZ(S) == 1 && *S.begin() == pii(1, n)) {
      cout << lim << '\n';
      continue;
    }
    if (S.begin() -> fi == 1 && prev(S.end()) -> se == n) {
      int L = S.begin() -> se, R = n - (prev(S.end()) -> fi) + 1;
      del(L), del(R), add(L + R);
    }
    int ans = 1e9;
    rep (i, 0, lim) chkmn(ans, i + sum[i]);
    cout << ans << '\n';
    if (S.begin() -> fi == 1 && prev(S.end()) -> se == n) {
      int L = S.begin() -> se, R = n - (prev(S.end()) -> fi) + 1;
      add(L), add(R), del(L + R);
    }
  }
}

int main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) work();
}