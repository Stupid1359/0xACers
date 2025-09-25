#include <bits/stdc++.h>
using namespace std;
constexpr int N = 4e6 + 5;
int n, m, pos[N], pre[N], dp[N], mx[N], ans;
vector<bool> x, a[N];
auto read() {
  string s;
  cin >> s;
  vector<bool> res(m * 5);
  for (int i = 0; i < m; i++) {
    int c = isdigit(s[i]) ? s[i] - '0' : s[i] - 'a' + 10;
    for (int j = 0; j < 5; j++) res[i * 5 + j] = (c >> (4 - j)) & 1;
  }
  return res;
}
void work() {
  cin >> n >> m;
  x = read();
  for (int i = 1; i <= n; i++) a[i] = read();
  int p = m * 5 - 1;
  while (p >= 0 && x[p]) x[p--] = false;
  if (p < 0) {
    cout << n << '\n';
    return;
  }
  x[p] = true;
  iota(pos + 1, pos + n + 1, 1);
  ans = -1;
  for (int d = 0; d < (m * 5); d++) {
    for (int i = 1; i <= n; i++) pre[i] = a[i][d] ? pre[i - 1] : i;
    if (x[d]) {
      for (int i = 1; i <= n; i++) {
        int cur = min(pos[i], pre[i]);
        dp[i] = cur ? mx[cur - 1] + 1 : -1;
        mx[i] = max(mx[i - 1], dp[i]);
      }
      ans = max(ans, dp[n]);
    } else {
      for (int i = 1; i <= n; i++) pos[i] = min(pos[i], pre[i]);
    }
  }
  cout << ans << '\n';
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) work();
}