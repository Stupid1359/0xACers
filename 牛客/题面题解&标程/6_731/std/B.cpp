#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t; cin >> t;
  while (t --) {
    int n, y, M; cin >> n >> y >> M;
    vector<vector<int>> v;
    for (int i = 1; i <= n; i ++) {
      int l, x; cin >> l;
      vector<int> a;
      while (l --) {
        cin >> x;
        a.push_back(x);
      }
      v.push_back(a);
    }

    auto check = [&] (i64 x) {
      for (auto &arr : v) {
        i64 nx = 0;
        for (auto &ele : arr) {
          if (ele >= x) return -1;
          nx = min(nx * x + ele, 1000000001ll);
        }
        x = nx;
      }
      if (x < y) return -1;
      if (x > y) return 1;
      return 0;
    };

    int l = 1, r = M + 1;
    while (l < r - 1) {
      int m = (l + r) >> 1;
      if (check(m) < 0)
        l = m;
      else
        r = m;
    }
    if (r == M + 1 || check(r) != 0) {
      puts("-1 -1");
    }
    else {
      int ans1 = r;
      l = ans1, r = M + 1;
      while (l < r - 1) {
        int m = (l + r) >> 1;
        if (check(m) == 0)
          l = m;
        else
          r = m;
      }
      printf("%d %d\n", ans1, l);
    }
  }
}