#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7;
int T, sum;
int a[17];
bool check(int x)
{
	int l = 0, r = 0;
	for (int i = 1; i <= 13; i++)
	{
		int R = a[i] / 3;
		int L = (a[i] - sum + 3 * x);
		if (L < 0)
			L = 0;
		else
			L = (L + 1) / 2;
		if (L > R)
			return false;
		l += L;
		r += R;
	}
	if (l <= x && r >= x)
		return true;
	return false;
}

void solve()
{
	for (int i = 1; i <= 13; i++)
		cin >> a[i];
	sum = 0;
	for (int i = 1; i <= 13; i++)
		sum += a[i];
	int L = 0, R = sum / 4;
	while (L < R)
	{
		int mid = (L + R + 1) >> 1;
		if (check(mid))
			L = mid;
		else
			R = mid - 1;
	}
	cout << L << "\n";
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen("2.in","r",stdin);
	//freopen("2.out","w",stdout);
	cin >> T;
	while (T--)
		solve();
}
