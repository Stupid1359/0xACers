// 替换万能头文件为标准头文件集合
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define ssz(x) (int((x).size()))

auto chmax = [](auto& x, auto y) { if (x < y) x = y; };
auto chmin = [](auto& x, auto y) { if (y < x) x = y; };

using ll = long long;
using db = long double;
const int N = 3e5;

struct point
{
  int x, y;
  point operator-(const point& rhs) {
    return { x - rhs.x, y - rhs.y };
  }
};
point a[N];
db ar[N];
bool gd[N];
map<db, int> cv;
int px[N];

ll det(const point& p, const point& q) {
  return 1ll * p.x * q.y - 1ll * p.y * q.x;
}

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int cas, n;
  
  auto nx = [&](auto p) {
    auto q = next(p);
    return q == cv.end() ? cv.begin() : q;
  };
  auto pr = [&](auto p) {
    return prev(p == cv.begin() ? cv.end() : p);
  };
  auto ls = [&](point i, point j, point p) {
    return det(j - i, p - i) >= 0;
  };
  
  point O; int k;
  auto build = [&](int l, int r)
  {
    cv.clear();
    k = px[r], O = {
      int((ll(a[k - 1].x) + a[k].x + a[k + 1].x) / 3),
      int((ll(a[k - 1].y) + a[k].y + a[k + 1].y) / 3)
    };
    for (int i = l; i <= r; i++)
    {
      auto t = a[i] - O;
      cv[ar[i] = atan2(t.y, t.x)] = i;
    }
  };
  
  cin >> cas;
  while (cas--)
  {
    cin >> n;
    // cerr << n << endl;
    for (int i = 0; i < n; i++)
    {
      cin >> a[i].x >> a[i].y;
      a[i].x *= 3, a[i].y *= 3;
    }
    px[1] = 0;
    for (int i = 1; i < n - 1; i++)
    {
      gd[i] = (det(a[i] - a[i - 1], a[i + 1] - a[i]) == 0);
      px[i + 1] = (gd[i] ? px[i] : i);
    }
    int i = min(n, 2), j = 0;
    while (i < n && gd[i - 1])
      i++;
    if (i == n)
    {
      cout << 1ll * n * (n + 1) / 2 << "\n";
      continue;
    }
    build(0, i), i++;
    ll ans = 1ll * (i + 1) * i / 2;
    for (; i < n; i++)
    {
      while (true)
      {
        auto t = a[i] - O;
        auto it = cv.lower_bound(ar[i] = atan2(t.y, t.x));
        if (it == cv.end())
          it = cv.begin();
        auto pi = pr(it);
        if (ls(a[it->second], a[nx(it)->second], a[i]) && ls(a[pr(pi)->second], a[pi->second], a[i]) && ls(a[it->second], a[pi->second], a[i]))
        {
          cv[ar[i]] = i;
          break;
        }
        j++;
        if (j >= k)
        {
          if (px[i - 1] <= j)
          {
            build(j, i);
            break;
          }
          build(j, i - 1);
        }
        else
          cv.erase(ar[j - 1]);
      }
      ans += i - j + 1;
      // cerr << i << " " << j << " " << k << endl;
    }
    /*
    cerr << fixed << setprecision(17);
    for (int i = 0; i < n; i++)
      cerr << ar[i] << " \n"[i == n - 1];
    */
    cout << ans << "\n";
  }
  
  return 0;
}