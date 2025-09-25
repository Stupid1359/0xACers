#include <bits/stdc++.h>
using namespace std;
 
const int mod = 998244353;
 
long long quickPow(long long base, long long power, long long mod) {
    if (power == 0) return 1 % mod;
    long long cur = quickPow(base, power / 2, mod);
    return power & 1 ? base * cur % mod * cur % mod : cur * cur % mod; 
}
 
void add(int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}
 
void sub(int &x, int y) {
    x -= y;
    if (x < 0) x += mod;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int t;
    cin >> t;
 
    while (t --) {
        int n, q;
        cin >> n >> q;
 
        vector<int> parent(n, -1), col_l(n), col_r(n), prob(n);
 
        for (int i = 1; i < n; i ++)
            cin >> parent[i], parent[i] --;
        
        for (auto &l: col_l) cin >> l;
        for (auto &r: col_r) cin >> r, r ++;
        
        vector<vector<int>> sons(n);
        for (int i = 1; i < n; i ++)
            sons[parent[i]].emplace_back(i);
 
        vector<int> ls(n), rs(n), sz(n, 1);
        int tmstamp = 0;
 
 
        auto dfs = [&] (auto &self, int u) -> void { 
            ls[u] = tmstamp ++;
            for (auto &v: sons[u])
                self(self, v), sz[u] += sz[v];
            rs[u] = tmstamp;
        };
 
        dfs(dfs, 0);
 
        auto intersect = [&] (int u, int v) -> int {
            return max(0, min(col_r[u], col_r[v]) - max(col_l[u], col_l[v]));
        };
 
        auto intersect3 = [&] (int u, int v, int w) -> int {
            return max(0, min({col_r[u], col_r[v], col_r[w]}) - max({col_l[u], col_l[v], col_l[w]}));
        };
 
        vector<int> cur_x1(n), cur_x2(n), cur_xy(n), prob_parent(n);
 
        auto update = [&] (int u) -> array<int, 3> {
            array<int, 3> ans;
            ans[0] = 0, ans[1] = 0, ans[2] = 0;
            
            prob[u] = quickPow(col_r[u] - col_l[u], mod - 2, mod);
 
            for (auto &v: sons[u]) {
                prob_parent[v] = 1ll * intersect(u, v) * prob[u] % mod * prob[v] % mod;
                add(ans[0], prob_parent[v]);
                add(ans[1], 1ll * prob_parent[v] * prob_parent[v] % mod);
            }
 
            for (auto &v1: sons[u]) {
                for (auto &v2: sons[u]) {
                    if (v1 == v2) break;
                    add(ans[2], 1ll * intersect3(u, v1, v2) * prob[u] % mod * prob[v1] % mod * prob[v2] % mod);
                    sub(ans[2], 1ll * prob_parent[v1] * prob_parent[v2] % mod);
                }
            }
 
            for (auto &v1: sons[u]) {
                for (auto &v2: sons[v1]) {
                    add(ans[2], 1ll * intersect3(u, v1, v2) * prob[u] % mod * prob[v1] % mod * prob[v2] % mod);
                    sub(ans[2], 1ll * prob_parent[v1] * prob_parent[v2] % mod);
                }
            }
 
            return ans;
        };
 
        for (int i = n - 1; i >= 0; i --) {
            auto res = update(i);
            cur_x1[i] = res[0];
            cur_x2[i] = res[1];
            cur_xy[i] = res[2];
        }
 
        vector<int> fen_x1(n + 1, 0), fen_x2(n + 1, 0), fen_xy(n + 1, 0);
 
        for (int i = 0; i < n; i ++) {
            fen_x1[ls[i] + 1] = cur_x1[i];
            fen_x2[ls[i] + 1] = cur_x2[i];
            fen_xy[ls[i] + 1] = cur_xy[i];
        }
 
        for (int i = 1; i <= n; i ++) {
            if (i + (i & -i) <= n) {
                int ni = i + (i & -i);
                add(fen_x1[ni], fen_x1[i]);
                add(fen_x2[ni], fen_x2[i]);
                add(fen_xy[ni], fen_xy[i]);
            }
        }
 
        auto fen_add = [&] (int u, int val, vector<int> &fen) -> void {
            int idx = ls[u] + 1;
            for (int i = idx; i <= n; i += i & -i)
                add(fen[i], val);
        };
 
        auto fen_pref_sum = [&] (int idx, vector<int> &fen) -> int {
            int ans = 0;
            for (int i = idx; i > 0; i -= i & -i)
                add(ans, fen[i]);
            return ans;
        };
 
        auto query = [&] (int u, vector<int> &fen) -> int {
            int l = ls[u], r = rs[u];
            int ans = fen_pref_sum(r, fen);
            sub(ans, fen_pref_sum(l, fen));
            return ans;
        };
 
        while (q --) {
            int t;
            cin >> t;
 
            if (t == 1) {
                int u, l, r;
                cin >> u >> l >> r;
                u --, r ++;
 
                col_l[u] = l, col_r[u] = r;
 
                for (int i = 0; i < 3; i ++) {
                    auto res = update(u);
 
                    sub(res[0], cur_x1[u]);
                    sub(res[1], cur_x2[u]);
                    sub(res[2], cur_xy[u]);
 
                    fen_add(u, res[0], fen_x1);
                    fen_add(u, res[1], fen_x2);
                    fen_add(u, res[2], fen_xy);
 
                    add(cur_x1[u], res[0]);
                    add(cur_x2[u], res[1]);
                    add(cur_xy[u], res[2]);
 
                    u = parent[u];
                    if (u < 0) break;
                }
            }
            else {
                int u;
                cin >> u;
                u --;
 
                int ex1 = query(u, fen_x1), ex2 = query(u, fen_x2), exy = query(u, fen_xy);
                int ans1 = sz[u], ans2 = ex1;
 
                sub(ans1, ex1);
 
                sub(ans2, ex2);
                add(ans2, exy);
                add(ans2, exy);
 
                cout << ans1 << ' ' << ans2 << '\n';
            }
        }
    }
 
    return 0;
}
