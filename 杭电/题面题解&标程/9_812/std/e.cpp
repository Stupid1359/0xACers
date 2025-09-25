#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int Mod = 998244353;
const int N = 210;
const int M = 1e7 + 10;
const int K = 1e5 + 10;
int k, n, m, c[K], d[K], dp[N][N][N], val[N][N];
int fac[M], ifac[M], inv[M];
map<int, int> t2;

int poww(int a, int b = Mod - 2) {
    int res = 1;
    while(b) {
        if (b & 1) res = res * a % Mod;
        a = a * a % Mod, b >>= 1;
    }
    return res;
}

void init(int k) {
    fac[0] = 1;
    for (int i = 1; i <= k; i++) fac[i] = fac[i - 1] * i % Mod;
    ifac[k] = poww(fac[k]);
    for (int i = k - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % Mod;
    for (int i = 1; i <= k; i++) inv[i] = ifac[i] * fac[i - 1] % Mod;
}

signed main() {
    cin.sync_with_stdio(false), cin.tie(0);
    cin >> k >> n >> m;
    init(k);
    vector<pair<int, int>> v;
    for (int i = 1; i <= n; i++) {
        int a, b; cin >> a >> b;
        v.push_back({a, b});
    }
    sort(v.begin(), v.end());
    for (int i = 1; i <= m; i++) {
        cin >> c[i] >> d[i];
        t2[c[i]] += d[i];
    }
    vector<pair<int, int>> tmp;
    // x -1, y +1
    for (auto [x, y] : v) {
        int cnt = t2[x - 1];
        if (cnt > y) {
            cout << "0\n";
            return 0;
        }
        int del = cnt, add = y - cnt;
        tmp.push_back({del, add});
        int &X = t2[x + 1];
        if (X >= add) X -= add;
        else {
            cout << "0\n";
            return 0;
        }
    }

    for (int j = 0; j <= 200; j++)
        for (int k = 0; j + k <= 200; k++)
            for (int i = 0; i <= 200; i++){
                if (j == 0 && k == 0) dp[i][j][k] = 1;
                else {
                    if (j != 0 && i != 0) (dp[i][j][k] += dp[i - 1][j - 1][k] * i) %= Mod;
                    if (k != 0) (dp[i][j][k] += dp[i + 1][j][k - 1]) %= Mod;
                }
            }
    // !! need write chazhi
    for (int j = 0; j <= 200; j++) {
        for (int i = 0; i <= j; i++) {
            int S = 1;
            for (int k = 0; k <= j; k++)
                if (k != i) S = S * (i - k + Mod) % Mod;
            val[j][i] = poww(S);
        }
    }
    auto calc = [](int i, int j, int k) -> int {
        if (i <= j) return dp[i][j][k];
        //0 - j -> i
        // cerr << i << ' ' << j << ' ' << k << ' ' << dp[0][j][k] << ' ' << dp[1][j][k] << ' ' << dp[2][j][k] << '\n';
        // cerr << val[1][0] << ' ' << val[1][1] << '\n';
        int S = fac[i] * ifac[i - j - 1] % Mod, res = 0;
        for (int t = 0; t <= j; t++)
            (res += dp[t][j][k] * S % Mod * inv[i - t] % Mod * val[j][t]) %= Mod;
        // cerr << res << '\n';
        return res;
    };
    int now = 0, ans = 1;
    for (auto [del, add] : tmp) {
        // !! need write chazhi
        // (ans *= dp[now][del][add]) %= Mod;
        // cerr << add << ' ' << del << '\n';
        // cerr << now << ' ' << del << ' ' << add << ' ' << calc(now, del, add) << '\n';
        (ans *= calc(now, del, add)) %= Mod;
        now += add - del;
        if (now < 0 || now > k) {
            cout << "0\n";
            return 0;
        }
    }
    if (now != 0) cout << "0\n";
	else cout << ans << '\n';
}
