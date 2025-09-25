#include <bits/stdc++.h>
using namespace std;

int n;
int a[200010], b[200010];
vector<int> g[200010];

int fa[200010], tot_sz[200010];
int deg[200010], tot_deg[200010], tot_edge[200010];

int ans;

vector<tuple<int, int, int, int>> add_list;

int getf(int x) {
  return x == fa[x] ? x : getf(fa[x]);
}

int coef(int r) {
  return tot_edge[r] ? max(1, tot_deg[r] / 2) : 0;
}

int upward(int a, int q) {
  int ta = a;
  int delta = (deg[a] == 0 ? 1 : -1);
  deg[a] ^= 1;
  while (1) {
    if (ta == fa[ta]) {
      ans -= coef(ta);
    }
    tot_deg[ta] += delta;
    tot_edge[ta] += q;
    if (ta == fa[ta]) {
      ans += coef(ta);
      break;
    }
    ta = fa[ta];
  }
  return ta;
}

void add(int a, int b) {
  int ta = upward(a, 1);
  int tb = upward(b, 1);
  if (tot_sz[ta] > tot_sz[tb]) {
    swap(a, b);
    swap(ta, tb);
  }
  add_list.emplace_back(a, b, ta, tb);
  if (ta != tb) {
    ans -= coef(ta) + coef(tb);
    fa[ta] = tb;
    tot_sz[tb] += tot_sz[ta];
    tot_edge[tb] += tot_edge[ta];
    tot_deg[tb] += tot_deg[ta];
    ans += coef(tb);
  }
}

void del(int a, int b, int ta, int tb) {
  if (ta != tb) {
    ans -= coef(tb);
    tot_sz[tb] -= tot_sz[ta];
    tot_edge[tb] -= tot_edge[ta];
    tot_deg[tb] -= tot_deg[ta];
    fa[ta] = ta;
    ans += coef(ta) + coef(tb);
  }
  upward(a, -1);
  upward(b, -1);
}

void del_multi(int cnt) {
  while (cnt --) {
    auto [a, b, ta, tb] = add_list.back();
    add_list.pop_back();
    del(a, b, ta, tb);
  }
}

int sz[200010], hv[200010];
int ans_list[200010];
int node[200010], L[200010], R[200010], idx;
void dfs1(int x, int f) {
  sz[x] = 1;
  L[x] = ++ idx;
  node[idx] = x;
  for (auto v : g[x]) if (v != f) {
    dfs1(v, x);
    if (sz[v] > sz[hv[x]])
      hv[x] = v;
    sz[x] += sz[v];
  }
  R[x] = idx;
}

void dfs2(int x, int f, bool keep) {
  for (auto v : g[x]) if (v != f && v != hv[x]) {
    dfs2(v, x, false);
  }
  if (hv[x]) {
    dfs2(hv[x], x, true);
  }
  for (auto v : g[x]) if (v != f && v != hv[x]) {
    for (int i = L[v]; i <= R[v]; i ++) {
      int cur = node[i];
      add(a[cur], b[cur]);
    }
  }
  add(a[x], b[x]);
  ans_list[x] = ans;
  if (!keep) {
    del_multi(sz[x]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; i ++) cin >> a[i];
  for (int i = 1; i <= n; i ++) cin >> b[i];
  for (int i = 1, u, v; i < n; i ++) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 1; i <= n; i ++) {
    fa[i] = i;
    tot_sz[i] = 1;
    deg[i] = 0;
    tot_deg[i] = 0;
    tot_edge[i] = 0;
  }
  dfs1(1, 1);
  dfs2(1, 1, true);
  for (int i = 1; i <= n; i ++) {
    printf("%d ", ans_list[i]);
  }
}
