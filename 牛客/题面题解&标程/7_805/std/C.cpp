#include <bits/stdc++.h>
using namespace std;
void solve()
{
	int n; cin >> n;
	vector <int> a(n);
	for (int &x : a) cin >> x;
	int ans = 0;
	for (int i = n - 2; i >= 0; --i)
	{
		ans = max(ans, a[i] - a[i + 1]);
		a[i] = min(a[i], a[i + 1]);
	}
	cout << ans << '\n';
}
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}
