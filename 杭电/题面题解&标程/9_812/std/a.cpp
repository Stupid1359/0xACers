#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

const int M = 2e5 + 10;
const int lim = 35;
int n, ls[M], rs[M], dp[M][lim + 5], f[lim + 5], sz[M];

void dfs(int u) {
    sz[u] = 1;
    if (ls[u]) dfs(ls[u]), sz[u] += sz[ls[u]];
    if (rs[u]) dfs(rs[u]), sz[u] += sz[rs[u]];
    dp[u][0] = sz[u], dp[u][1] = sz[u] - 1;
    for (int i = 2; i <= lim; i++)
        dp[u][i] = min({dp[ls[u]][i - 1] + dp[rs[u]][i - 1],
        dp[ls[u]][i - 1] + dp[rs[u]][i - 2], dp[ls[u]][i - 2] + dp[rs[u]][i - 1]});
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> ls[i] >> rs[i];
    dfs(1);
    int ans = n;
    for (int i = 0; i <= lim; i++) ans = min(ans, dp[1][i]);
    cout << ans << '\n';
}

int main() {
    f[1] = 1;
    for (int i = 2; i <= lim; i++) f[i] = f[i - 1] + f[i - 2] + 1;
    // for (int i = 1; i <= lim; i++) cerr << f[i] << (i == lim ? '\n' : ' ');
    for (int i = 0; i <= lim; i++) dp[0][i] = f[i];
    int T; cin >> T;
    while(T--) solve();
}