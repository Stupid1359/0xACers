#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <vector>
using namespace std;
const int mod = 998244353;
using ll = long long;
using pii = pair<int, int>;
const int N = 330;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> g(N), a(n);
    vector<int> p(n), block_idx(n), nxt(n);
    vector<vector<int>> ip(n);

    vector<ll> bru(n);
    for (int i = 0; i < n; ++i) cin >> p[i], p[i]--, ip[p[i]].push_back(i);
    for (int i = n - 1, tmp = n; i >= 0; --i) nxt[i] = tmp, ip[i].size() == 0 ? 0 : tmp = i;
    vector<ll> V;
    for (int i = 0; i < n;) {
        int j = i + 1, cur = ip[i].size();
        while (j < n && cur + ip[j].size() < N) cur += ip[j++].size();
        for (int k = i; k < j; ++k) block_idx[k] = V.size();
        V.push_back(i);
        i = j;
    }

    int cnt = V.size();
    V.push_back(n);
    vector<vector<int>> f(cnt, vector<int>(N));
    vector<ll> b(cnt);
    assert(cnt < 2 * N);
    for (int i = 0; i < n; ++i) f[block_idx[p[i]]][i / N]++;
    for (int i = 0; i < cnt; ++i)
        for (int j = 1; j < N; ++j) f[i][j] += f[i][j - 1];
    ll lst_ans = 0;
    for (int i = 0; i < q; ++i) {
        ll op, l, r, x;
        cin >> op >> l >> r;
        l ^= lst_ans, r ^= lst_ans;
        l--, r--;
        if (op == 1) {
            cin >> x, x ^= lst_ans;
            int lb = l == 0 ? 0 : block_idx[l - 1] + 1;
            int rb = r == n - 1 ? cnt - 1 : block_idx[r + 1] - 1;
            for (int i = lb; i <= rb; ++i) b[i] += x;
            vector<pii> lr;
            if (lb <= rb) lr.push_back({l, V[lb] - 1}), lr.push_back({V[rb + 1], r});
            if (lb > rb) lr.push_back({l, r});
            for (const auto [l, r] : lr) {
                for (int i = l; i <= r; i = nxt[i]) {
                    // assert(0);
                    a[i] += x;
                    for (const auto u : ip[i]) g[u / N] += x;
                }
            }
        } else {
            ll ans = 0, ans1 = 0;
            if (r - l <= 2 * N) {
                for (int i = l; i <= r; ++i) ans += a[p[i]] + b[block_idx[p[i]]];
            } else {
                int lb = l / N + 1, rb = r / N;
                for (int i = 0; i < cnt; ++i) ans += b[i] * (f[i][rb - 1] - f[i][lb - 1]);
                for (int i = lb; i < rb; ++i) ans += g[i];
                for (int i = l; i < N * lb; ++i) ans += a[p[i]] + b[block_idx[p[i]]];
                for (int i = rb * N; i <= r; ++i) ans += a[p[i]] + b[block_idx[p[i]]];
            }
            cout << ans << "\n";
            lst_ans = ans;
        }
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    int t = 1;
    while (t--) solve();
}
/*

*/