#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 1500 * 1500 * 3;
const int mod = 998244353, inv2 = (mod + 1) / 2;
int n, mx[1501];
i64 V, dp[N + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> V;
    for (int i = 1, a, b; i <= n; i++) {
        cin >> a >> b;
        mx[a] = max(mx[a], b);
    }
    vector<pair<i64, i64>> tmp;
    for (int i = 1; i <= 1500; i++) {
        if (!mx[i]) continue;
        tmp.push_back({mx[i], i});
    }
    sort(tmp.begin(), tmp.end(), [&](auto &t1, auto &t2) {
        return t1.first * t2.second > t1.second * t2.first;
    });

    for (int i = 1; i <= N; i++) {
        int lim = min((int)tmp.size(), (N + i - 1) / i);
        for (int j = 0; j < lim; j++) {
            if (tmp[j].second > i) continue;
            dp[i] = max(dp[i], dp[i - tmp[j].second] + tmp[j].first);
        }
    }

    auto [w, v] = tmp[0];
    i64 ans = 0;
    for (int i = 1; i <= V and i <= N; i++) {
        ans = (dp[i] % mod + ans) % mod;
    }
    if (V > N) {
        i64 len = (V - N) / v;
        if (len) {
            i64 b = 0, d = w * v % mod;
            for (int i = 1; i <= v; i++) {
                b = (b + dp[N + i - v] + w) % mod;
            }
            ans += len % mod * ((d % mod * ((len - 1) % mod) % mod + b + b) % mod) % mod * inv2 % mod;
            ans %= mod;
        }
        int remain = (V - N) % v;
        for (int i = 1; i <= remain; i++) {
            ans = (ans + dp[N + i - v]) % mod;
            ans = (ans + (len + 1) % mod * w % mod) % mod;
        }
    }
    cout << ans << '\n';
}
/*

*/