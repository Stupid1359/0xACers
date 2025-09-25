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
 
        vector<long long> nums(n);
        for (auto &x: nums)
            cin >> x;
        
        bool flg = true;
        for (int i = 0; i < n && flg; i ++) {
            for (int j = 0; j < i && flg; j ++) {
                if ((nums[i] ^ nums[j]) <= max(nums[i], nums[j])) {
                    flg = false;
                }
            }
        }
 
        cout << (flg ? "YES" : "NO") << '\n';
    }
 
    return 0;
}
