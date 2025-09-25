#include <bits/stdc++.h>
#include <cassert>
#define int long long
using namespace std;

const int M = 1010;
int n, d1[M][M], d2[M][M], e1[M][M], e2[M][M], fa[M];
vector<int> G[M];

int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> d1[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> d2[i][j];
            if (d2[i][j] < d1[i][j]) swap(d2[i][j], d1[i][j]);
            // d1[i][j] <= d2[i][j]
        }
    for (int i = 1; i <= n; i++)
        if (d1[i][i] != 0 || d2[i][i] != 0) {
            // cout << "NO\n";
            assert(0);
            return;
        }
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (d1[i][j] != d1[j][i] || d2[i][j] != d2[j][i]) {
                // cout << "NO\n";
                assert(0);
                return;
            }
    vector<tuple<int, int, int>> E;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            E.push_back({d1[i][j] + d2[i][j], i, j});
    sort(E.begin(), E.end());
    vector<pair<int, int>> ans;
    for (int i = 1; i <= n; i++) fa[i] = i;
    //step 1: find the tree
    for (auto [w, u, v] : E) {
        if (find(u) == find(v)) continue;
        fa[find(u)] = find(v);
        G[u].push_back(v), G[v].push_back(u);
        ans.push_back({u, v});
    }
    vector<int> nowv;
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        nowv.push_back(u);
        // cerr << "ok " << u << '\n';
        for (auto v : G[u]) {
            if (v == fa) continue;
            int w1 = d1[u][v], w2 = d2[u][v];
            auto check = [&]() -> bool {
                for (auto x : nowv) {
                    int t1 = e1[x][u] + w1, t2 = e2[x][u] + w2;
                    if (t1 > t2) swap(t1, t2);
                    if (t1 != d1[x][v] || t2 != d2[x][v]) return false;
                }
                for (auto x : nowv)
                    e1[x][v] = e1[v][x] = w1 + e1[x][u],
                    e2[x][v] = e2[v][x] = w2 + e2[x][u];
                return true;
            };
            if (!check()) {
                swap(w1, w2);
                if (!check()) {
                    // cerr << "error :" << v << '\n';
                    assert(0);
                    return;
                }
            }
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);
    for (auto [u, v] : ans)
        cout << u << ' ' << v << ' ' << e1[u][v] << ' ' << e2[u][v] << '\n';
}

void clear() {
    for (int i = 1; i <= n; i++) G[i].clear();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) e1[i][j] = e1[j][i] = 0;
}

signed main() {
    int T; cin >> T;
    while(T--) solve(), clear();
}
/*
还不知道对不对
*/