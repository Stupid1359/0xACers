#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

	int t;
	cin >> t;

    long long inf = 1e18;

	while (t --) {
		int n, v;
		cin >> n >> v;

        vector<int> hs(n), ss(n), ds(n);
		for (int i = 0; i < n; i ++)
            cin >> hs[i] >> ss[i] >> ds[i];

        long long ans = 0;
        
        for (int unused = 0; unused < v; unused ++) {
            int used = v - unused;
            vector<vector<long long>> values(used + 1);

            for (int i = 0; i < n; i ++)
                if (ss[i] <= used)
                    values[ss[i]].emplace_back(1ll * unused * ds[i] - hs[i]);

            vector<long long> dp(used + 1, -inf);
            dp[0] = 0;

            for (int i = 1; i <= used; i ++) {
                int k = min(used / i, (int)values[i].size());
                nth_element(values[i].begin(), values[i].begin() + k - 1, values[i].end());

                for (int idx = 0; idx < k; idx ++) {
                    for (int cur = used; cur >= i; cur --) {
                        dp[cur] = max(dp[cur], dp[cur - i] - values[i][idx]);
                    }
                }
            }
            
            ans = max(ans, dp[used]);
        }
        cout << ans << '\n';
	}

    return 0;
}