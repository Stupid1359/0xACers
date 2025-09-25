#include <bits/stdc++.h>
using namespace std;
int n, ans;
int l, r, T;
int a[2000005], f[2000005];
int main()
{
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--)
    {
        cin >> n;ans=1;
        for (int i = 1; i <= n; i++)
            cin >> a[i], f[a[i]] = i;
        l = r = f[n];
        for (int i = n - 1; i >= 1; i--)
        {
            l = min(f[i], l);
            r = max(f[i], r);
            ans = max(ans, (r - l + 1) - (n - i - 1));
        }
        cout << ans << '\n';
    }
    return 0;
}