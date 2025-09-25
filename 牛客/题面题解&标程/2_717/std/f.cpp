#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int t;
    cin >> t;
 
    while (t --) {
        int n, k;
        string s;
        cin >> n >> k >> s;
 
        vector<int> acc(2 * n + 1);
        for (int i = 0; i < n; i ++) {
            if (s[i] == '1') {
                acc[max(i - k, 0)] ++;
                acc[min(i + k + 1, 2 * n)] --;
                acc[max(i + n - k, 0)] ++;
                acc[min(i + n + k + 1, 2 * n)] --;
            }
        }
        
        for (int i = 0; i < n * 2; i ++)
            acc[i + 1] += acc[i];
        
        int ans = 0;
        for (int i = 0; i < n; i ++) {
            if (acc[i] == 0 && acc[i + n] == 0) {
                ans ++;
            }
        }
 
        int c = 0, res = 0;
 
        for (int i = 0; i < n * 2; i ++) {
            if (s[i % n] == '1') c = 0;
            else c ++;
            res = max(res, c);
        }
 
        cout << ans + max(max(0, res - k - 1) - max(0, res - 2 * k), 0) << '\n';
    }
 
    return 0;
}
