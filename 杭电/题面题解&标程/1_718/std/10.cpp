#include <bits/stdc++.h>
#define int long long
using namespace std;
const int P = 2001;
const int N = 2005;
int T, ans, n, sum[N], s[N * 2], a[N], b[N], j;
signed main()
{
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--)
	{
		ans = 0;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		for (int i = 1; i <= n; i++)
		{
			memset(s, 0, sizeof(s));
			for (j = 1; j <= n; j++)
				b[j] = a[j] > a[i] ? 1 : -1;
			sum[0] = 0;
			b[i] = 0;
			for (j = 1; j <= n; j++)
				sum[j] = sum[j - 1] + b[j];
			for (j = 0; j < i; j++)
				s[sum[j] + P] += j + 1;
			for (; j <= n; j++)
				ans += j * s[sum[j] + P] * a[i];
		}
		cout << ans << '\n';
	}
}