#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a), i##ABRACADABRA = (b); i <= i##ABRACADABRA; i++)
#define drep(i, a, b) for (int i = (a), i##ABRACADABRA = (b); i >= i##ABRACADABRA; i--)
using namespace std;
using ll = long long;

int n, a[5000010], cnt[5000010], R[5000010], x, y, z;
ll res;

#define max(x,y) 

int main() {
  ios_base :: sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--){
    res = 0;
    cin >> n >> x >> y >> z;
    rep(i, 0, n + 5)
      cnt[i] = R[i] = 0;
    rep(i, 1, n)
      cin >> a[i];
    rep(i, 1, n)
      ++cnt[a[i]];
    rep(i, 1, n)
      rep(j, 1, cnt[i])
        ++R[j];
    drep(i, n, 1)
      R[i - 1] += R[i];
    rep(i, 0, n) {
      // i 个重置
      int Z = i, Y = R[i + 2], X = n - Y - Z;
      ll val = 1ll * Z * z + 1ll * Y * y + 1ll * X * x;
      res = res > val ? res : val;
      if (!Y) break;
    }
    cout << res << '\n';
  }
  return 0;
} 