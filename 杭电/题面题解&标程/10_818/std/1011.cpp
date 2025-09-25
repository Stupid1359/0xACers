#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e4 + 5, M = 1e5 + 5, B = 512;
int n, m, eu[M], ev[M], ans[M], deg[N];
vector<int> key, g[N];
bitset<B * 2> f[N], ex[B * 2];
bool bfs(int s, int t) {
  bitset<B * 2> q, vis;
  q.set(s);
  while (!q.test(t)) {
    int u = (q & ~vis)._Find_first();
    if (u == B * 2) return false;
    vis.set(u);
    q |= f[key[u]], q |= ex[u];
  }
  return true;
}
void solve(int l, int r) {
  key.clear();
  for (int i = l; i <= r; i++) key.push_back(eu[i]), key.push_back(ev[i]);
  sort(key.begin(), key.end()), key.erase(unique(key.begin(), key.end()), key.end());
  for (int i = 1; i <= n; i++) f[i].reset();
  for (int i = 0; i < key.size(); i++) f[key[i]].set(i);
  fill(deg + 1, deg + n + 1, 0);
  for (int u = 1; u <= n; u++) for (int v : g[u]) deg[v]++;
  queue<int> q;
  for (int i = 1; i <= n; i++) if (!deg[i]) q.push(i);
  while (q.size()) {
    int u = q.front();
    q.pop();
    for (int v : g[u]) {
      f[v] |= f[u];
      if (!--deg[v]) q.push(v);
    }
  }
  for (int i = 0; i < key.size(); i++) ex[i].reset();
  for (int i = l; i <= r; i++) {
    int u = lower_bound(key.begin(), key.end(), eu[i]) - key.begin();
    int v = lower_bound(key.begin(), key.end(), ev[i]) - key.begin();
    if (bfs(v, u)) ans[i] = 2;
    else {
      ans[i] = 1;
      g[ev[i]].push_back(eu[i]);
      ex[u].set(v);
    }
  }
}
void work() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) cin >> eu[i] >> ev[i];
  for (int i = 1; i <= m; i++) if (eu[i] == ev[i]) {
    cout << "-1\n";
    return;
  }
  for (int i = 1; i <= n; i++) g[i].clear();
  for (int i = 1; i <= m; i += B) solve(i, min(m, i + B - 1));
  for (int i = 1; i <= m; i++) cout << ans[i] << " \n"[i == m];
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) work();
}