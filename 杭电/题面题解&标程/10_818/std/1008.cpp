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

const int maxn = 100010;

int n, m, f[maxn], g[maxn], ans[maxn], tot, cntf, cntg, sumf, sumg;
pii wf[maxn], wg[maxn], wc[maxn];
vector<tuple<int, int, int>> vec;
string str[maxn];

void merge(int k, int o) {
  vec.clear();
  int px = 1, py = 1;
  while (px <= n && py <= n) {
    if (wf[px].fi <= wg[py].fi) {
      if (str[wf[px].se][k] == 'T') vec.emplace_back(wf[px].fi + o, wf[px].se, 0), cntf++;
      px++;
    } else {
      vec.emplace_back(wg[py].fi + o, wg[py].se, 1), cntg++;
      py++;
    }
  }
  while (px <= n) {
    if (str[wf[px].se][k] == 'T') vec.emplace_back(wf[px].fi + o, wf[px].se, 0), cntf++;
    px++;
  }
  while (py <= n) {
    vec.emplace_back(wg[py].fi + o, wg[py].se, 1), cntg++;
    py++;
  }
}

void work() {
  cin >> n >> m, vec.reserve(2 * n);
  rep (i, 1, n) cin >> str[i], ans[i] = f[i] = g[i] = 0;
  rep (i, 1, n) wf[i] = pii(0, i), wg[i] = pii(0, i);
  per (k, m - 1, 0) {
    rep (i, 1, n) swap(f[i], g[i]), swap(wf[i], wg[i]);
    cntf = 0, cntg = 0, sumf = 0, sumg = 0;
    merge(k, 1);
    for (auto [v, x, op] : vec) {
      if (!op) ans[x] -= sumg + cntg * v, sumf += v, cntf--;
      else ans[x] += 3 * (sumf + cntf * v), sumg += v, cntg--;
    }
    rep (i, 1, n) if (str[i][k] == 'T') ans[i] -= 2 * (min(f[i], g[i]) + 1);
    rep (i, 1, n) f[i]++, wf[i].fi++;
    cntf = 0, cntg = 0, sumf = 0, sumg = 0;
    merge(k, 0);
    for (auto [v, x, op] : vec) {
      if (!op) ans[x] += 3 * (sumg + cntg * v), sumf += v, cntf--;
      else ans[x] -= sumf + cntf * v, sumg += v, cntg--;
    }
    rep (i, 1, n) if (str[i][k] == 'T') ans[i] -= 2 * min(f[i], g[i]);
    rep (i, 1, n) if (str[i][k] != 'R') f[i] = 0;
    tot = 0;
    rep (i, 1, n) if (!f[wf[i].se]) wc[++tot] = pii(0, wf[i].se);
    rep (i, 1, n) if (f[wf[i].se]) wc[++tot] = wf[i];
    rep (i, 1, n) wf[i] = wc[i];
  }
  rep (i, 1, n) cout << ans[i] << " \n"[i == n];
}

int main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) work();
}