#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int t;
    cin >> t;
 
    while (t --) {
        int n;
        cin >> n;
    
        vector<int> cols(n + 1, 0);
        for (int i = 1; i <= n; i ++)
            cin >> cols[i];
        
        int c0 = 0, c1 = 0, c2 = 0;
    
        for (int i = 0; i < n; i ++) {
            if (cols[i] == 0 && cols[i + 1] == 1) c0 ++;
            else if (cols[i] == 0 && cols[i + 1] == -1) c1 ++;
            else if (cols[i] == -1 && cols[i + 1] == 1) c1 ++;
            else if (cols[i] == -1 && cols[i + 1] == -1) c2 ++;
        }
    
        int mod = 998244353;
        int rev2 = (mod + 1) / 2, rev4 = 1ll * rev2 * rev2 % mod;
    
        int ans = c0;
        ans += 1ll * c1 * rev2 % mod;
        ans %= mod;
        ans += 1ll * c2 * rev4 % mod;
        ans %= mod;
    
        for (int i = 0; i <= n; i ++) {
            if (cols[i] == -1) {
                ans += ans;
                if (ans >= mod) ans -= mod;
            }
        }
    
        cout << ans << '\n';
    }
 
    return 0;
}
