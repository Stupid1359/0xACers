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

const int maxn = 500010;
const int maxm = 800;
const int B = 300;

int n, m, cnt[maxn], G[maxm][maxm];
ll a[maxn], c[maxn], sum[maxn];
vector<int> fac[maxn];

inline ll mylcm(ll x, ll y) { return x / G[x][y % x] * y; }

int main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  cin >> n >> m;
  rep (i, 1, n) rep (j, 1, n / i) fac[i * j].emplace_back(i);
  rep (i, 1, n) cin >> a[i], cnt[i] = SZ(fac[i]);
  rep (i, 1, B) rep (j, 1, n / i) sum[i] += a[i * j];
  rep (i, 0, B) rep (j, 0, B) {
    if (!i || !j) G[i][j] = i + j;
    else if (i < j) G[i][j] = G[j % i][i];
    else G[i][j] = G[i % j][j];
  }
  while (m--) {
    int op, x, k;
    cin >> op >> x;
    if (op == 1) {
      cin >> k;
      if (x <= B) {
        c[x] += k;
      } else {
        for (int i = x; i <= n; i += x) a[i] += k;
      }
      rep (i, 1, B) sum[i] += 1ll * k * (n / mylcm(i, x));
    } else if (op == 2) {
      cin >> k;
      for (int i : fac[x]) a[i] += k;
      rep (i, 1, B) if (x % i == 0) sum[i] += 1ll * k * cnt[x / i];
    } else if (op == 3) {
      if (x <= B) {
        cout << sum[x] << '\n';
      } else {
        ll ans = 0;
        for (int i = x; i <= n; i += x) ans += a[i];
        rep (i, 1, B) ans += c[i] * (n / mylcm(i, x));
        cout << ans << '\n';
      }
    } else {
      ll ans = 0;
      for (int i : fac[x]) {
        ans += a[i];
        if (i <= B) ans += c[i] * cnt[x / i];
      }
      cout << ans << '\n';
    }
  }
}