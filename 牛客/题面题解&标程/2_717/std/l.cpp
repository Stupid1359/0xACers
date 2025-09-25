#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int t, mod = 998244353;
    cin >> t;
 
    while (t --) {
        int n;
        cin >> n;
 
        vector<int> nums(n);
        for (auto &x: nums)
            cin >> x, x --;
        
        vector<int> odd, even;
        vector<bool> vis(n, 0);
 
        for (int i = 0; i < n; i ++) {
            if (!vis[i]) {
                int cnt = 0;
                while (!vis[i]) {
                    vis[i] = 1;
                    cnt ++;
                    i = nums[i];
                }
                if (cnt & 1) odd.emplace_back(cnt);
                else even.emplace_back(cnt);
            }
        }
 
        if (odd.size() == 2) {
            int ans = 1ll * odd[0] * odd[1] % mod;
            for (auto &x: even) {
                if (x != 2) {
                    ans = 2ll * ans % mod;
                }
            }
            cout << ans << '\n';
        }
        else if (odd.size() == 0) {
            int v = 1;
            for (auto &x: even) {
                if (x != 2) {
                    v = 2ll * v % mod;
                }
            }
            int half_v = 1ll * v * (mod + 1) / 2 % mod;
 
            int ans = 0;
            for (auto &x: even) {
                if (x == 2) ans += v;
                else ans += 1ll * (x / 2) * (x / 2) % mod * half_v % mod;
                if (ans >= mod) ans -= mod;
            }
 
            cout << ans << '\n';
        }
        else cout << 0 << '\n';
    }
 
    return 0;
}
