#include <bits/stdc++.h>

constexpr int inf = 1e9;

struct MinCostMaxFlow {
  int n, s, t;
  std::vector<std::vector<std::tuple<int, int, int, int>>> g;
  std::vector<int> h, d;
  std::vector<std::pair<int, int>> from;
  MinCostMaxFlow(int m) : n(m + 2), s(n - 2), t(n - 1), g(n), h(n), d(n), from(n) {}
  void add(int u, int v, int flow, int cost) {
    g[u].emplace_back(v, flow, cost, g[v].size());
    g[v].emplace_back(u, 0, -cost, g[u].size() - 1);
  }
  void topo() {
    std::vector<int> deg(n);
    for (int u = 0; u < n; u++) {
      for (auto [v, flow, cost, id] : g[u]) {
        if (flow) deg[v]++;
      }
    }
    std::fill(h.begin(), h.end(), inf);
    std::queue<int> q;
    h[s] = 0;
    q.push(s);
    while (q.size()) {
      int u = q.front();
      q.pop();
      for (auto [v, flow, cost, id] : g[u]) {
        if (flow) {
          h[v] = std::min(h[v], h[u] + cost);
          if (!--deg[v]) q.push(v);
        }
      }
    }
  }
  bool dij() {
    std::fill(d.begin(), d.end(), inf);
    std::vector<std::vector<int>> buc(n);
    std::vector<bool> vis(n);
    int cur = 0;
    d[s] = 0;
    buc[0].push_back(s);
    while (true) {
      while (cur < n && buc[cur].empty()) cur++;
      if (cur == n) break;
      int u = buc[cur].back();
      buc[cur].pop_back();
      if (!vis[u]) {
        vis[u] = true;
        for (int i = 0; i < g[u].size(); i++) {
          auto [v, flow, cost, id] = g[u][i];
          int w = cost + h[u] - h[v];
          if (flow && d[v] > d[u] + w) {
            d[v] = d[u] + w;
            buc[d[v]].push_back(v);
            from[v] = std::make_pair(u, i);
          }
        }
      }
    }
    return d[t] != inf;
  }
  std::vector<int> flow() {
    int cost = 0;
    std::vector<int> res;
    topo();
    while (dij()) {
      for (int i = 0; i < n; i++) h[i] = std::min(inf, h[i] + d[i]);
      int fl = inf;
      for (int u = t; u != s; ) {
        int id = from[u].second;
        u = from[u].first;
        fl = std::min(fl, std::get<1>(g[u][id]));
      }
      for (int i = 0; i < fl; i++) {
        cost += h[t];
        res.push_back(cost);
      }
      for (int u = t; u != s; ) {
        int id = from[u].second, v = u;
        u = from[u].first;
        std::get<1>(g[u][id]) -= fl;
        std::get<1>(g[v][std::get<3>(g[u][id])]) += fl;
      }
    }
    return res;
  }
};

void work() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  std::vector<std::vector<int>> pos(m);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    pos[--a[i]].push_back(i);
  }
  MinCostMaxFlow f(n + m);
  f.add(f.s, 0, n, 0);
  for (int i = 0; i < n - 1; i++) f.add(i, i + 1, m, 0);
  f.add(n - 1, f.t, m, 0);
  for (int i = 0; i < m; i++) {
    if (pos[i].size() > 1) {
      f.add(pos[i][0], i + n, 1, 0);
      for (int j = 1; j < pos[i].size(); j++) f.add(i + n, pos[i][j], 1, -j);
    }
  }
  std::vector<int> cost = f.flow();
  for (int i = 0; i < m; i++) std::cout << n + cost[i] << " \n"[i + 1 == m];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t;
  std::cin >> t;
  while (t--) work();
}