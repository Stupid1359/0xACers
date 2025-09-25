#include <bits/stdc++.h>
using namespace std;

void work () {
	int n, m;
	cin >> n >> m;
	vector <int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	vector <int> id(n);
	iota(id.begin(), id.end(), 0);
	sort(id.begin(), id.end(), [&](int u, int v) { return a[u] < a[v]; });
	vector <int> rev(n);
	for (int i = 0; i < n; i++) rev[id[i]] = i;
	sort(a.begin(), a.end());

	vector <int> E(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u = rev[u - 1];
		v = rev[v - 1];
		E[v] |= 1 << u;
	}

	unordered_map <int, int> dp;
    auto solve = [&](auto &&self, int mask) -> int {
        if (mask == (1 << n) - 1) return 0;
        if (dp.count(mask)) return dp[mask];
        int cur = 0, ret = 0x3f3f3f3f;
        for (int j = 0; j < n; j++) {
            if ((~mask >> j) & 1 && (E[j] & mask) == E[j]) {
                cur |= 1 << j;
                ret = min(ret, self(self, mask | cur) + a[j]);
            }
        }
        return dp[mask] = ret;
    };
	cout << solve(solve, 0) << '\n';
    cerr << dp.size() << endl;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int T = 1;
	for (int ca = 1; ca <= T; ca ++)
		work();
}