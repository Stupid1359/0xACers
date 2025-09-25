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

const int maxn = 310;

int n, mod, A[maxn][maxn], f[maxn][maxn][2][2], g[maxn][maxn][2][2];

__int128 mu;
namespace barrett {
  inline ll reduce(ll x) {
    ll r = x - (mu * x >> 64) * mod;
    return r >= mod ? r - mod : r;
  }
  inline void setmod(ll mod) {
    mu = -1ull / mod;
  }
}
using namespace barrett;

inline void add(int &x, int y) { x += y; if (x >= mod) x -= mod; }
inline void sub(int &x, int y) { x -= y; if (x < 0) x += mod; }
inline int Add(int x, int y) { x += y; if (x >= mod) x -= mod; return x; }
inline int Sub(int x, int y) { x -= y; if (x < 0) x += mod; return x; }
inline int fpw(int a, ll p) { int e = 1; while (p) { if (p & 1) e = reduce(1ll * e * a); a = reduce(1ll * a * a), p >>= 1; } return e; }

void work() {
  memset(f, 0, sizeof(f));
  cin >> n >> mod, setmod(mod);
  rep (i, 0, n) {
    A[i][0] = 1;
    rep (j, 1, i) A[i][j] = Add(A[i - 1][j], reduce(1ll * j * A[i - 1][j - 1]));
  }
  f[1][0][0][1] = (n > 1), f[1][1][0][0] = (n > 2);
  cout << 1;
  rep (i, 2, n) {
    rep (j, 1, i - 1) rep (k, 0, i - 1) rep (ox, 0, 1) rep (oy, 0, 1) g[j][k][ox][oy] = f[j][k][ox][oy], f[j][k][ox][oy] = 0;
    rep (j, 1, i - 1) rep (k, 0, i - 1) rep (ox, 0, 1) rep (oy, 0, 1) {
      int lw = j - k - ox - oy;
      add(f[j][k][ox][oy], reduce(1ll * g[j][k][ox][oy] * (k + oy + lw)));
      add(f[j + 1][k][oy][0], reduce(1ll * g[j][k][ox][oy] * (j - 1 - lw + !ox)));
      add(f[j + 1][k + 1][oy][0], g[j][k][ox][oy]);
      if (k && j + 2 <= n) add(f[j + 1][k - 1][oy][1], reduce(1ll * g[j][k][ox][oy] * (j - 1 - lw + !ox) * k));
      if (j + 2 <= n) add(f[j + 1][k][oy][1], reduce(1ll * g[j][k][ox][oy] * (k + 1)));
    }
    int sum = 1;
    rep (j, 1, i) sum = reduce(1ll * i * sum);
    rep (j, 0, i - 1) rep (k, 0, i) rep (ox, 0, 1) rep (oy, 0, 1) if (j + oy <= i) sub(sum, reduce(1ll * f[j][k][ox][oy] * A[i - j - 1][k]));
    rep (ox, 0, 1) sub(sum, f[i][0][ox][0]);
    cout << " " << sum;
  }
  cout << '\n';
}

int main() {
  cin.tie(nullptr) -> ios::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) work();
}