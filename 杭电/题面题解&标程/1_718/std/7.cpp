#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;

void solve() {
    int n, x;
    cin >> n >> x;

    vector<vector<int>> E(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        E[u].push_back(v);
        E[v].push_back(u);
    }

    map<int, int> cnt;

    {
        int nx = x;
        for (int i = 2; i * i <= nx; i++) {
            int ct = 0;
            while (nx % i == 0) {
                nx /= i;
                ct++;
            }

            if (ct) {
                cnt[i] = ct;
            }
        }

        if (nx > 1) {
            cnt[nx] = 1;
        }
    }

    const int k = cnt.size();

    auto get = [&](int y) {
        if (lcm(x, y) != x) {
            return -1;
        }

        int val = 0;
        int j = 0;
        for (auto [v, c] : cnt) {
            int cur = 0;
            while (y % v == 0) {
                y /= v;
                cur++;
            }

            if (cur == c) {
                val |= (1 << j);
            }

            j++;
        }

        return val;
    };

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[i] = get(x);
    }

    ll ans = 0;

    vector<vector<int>> dp(n + 1, vector<int>(1 << k));

    auto dfs = [&](auto self, int u, int fa) -> void {
        for (auto v : E[u]) {
            if (v == fa) continue;
            self(self, v, u);
        }

        if (a[u] == -1) {
            return;
        }

        dp[u][a[u]] = 1;
        for (auto v : E[u]) {
            if (v == fa) continue;
            auto s = dp[u];

            for (int j = 0; j < k; j++) {
                for (int i = 0; i < (1 << k); i++) {
                    if (!(i >> j & 1)) {
                        s[i] += s[i ^ (1 << j)];
                    }
                }
            }

            for (int i = 0; i < (1 << k); i++) {
                int x = i | a[u];
                ans += 1ll * s[x ^ ((1 << k) - 1)] * dp[v][i];
                dp[u][x] += dp[v][i];
            }
        }

        if (a[u] == (1 << k) - 1) {
            ans++;
        }
    };

    dfs(dfs, 1, -1);
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}