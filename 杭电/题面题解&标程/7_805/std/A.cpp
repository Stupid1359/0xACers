#include "bits/stdc++.h"
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int m, k, n, i, j;
	cin >> m >> m >> k >> n;
	n *= n;
	vector<int> a(n);
	while (m--)
	{
		int op = 0, ans = 0;
		for (j = 0; j < k; j++)
		{
			for (int &x : a) cin >> x, --x;
			for (i = 0; i < n; i++) while (a[i] != i) swap(a[i], a[a[i]]), op ^= 1;
			ans |= op;
		}
		cout << ans;
	}
	cout << endl;
}
