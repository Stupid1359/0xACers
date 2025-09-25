#include "bits/stdc++.h"
using namespace std;
template<class T1> ostream &operator<<(ostream &cout, vector<T1> a) { int n = a.size(); if (!n) return cout; cout << a[0]; for (int i = 1; i < n; i++) cout << ' ' << a[i]; return cout; }
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(15);
	int T;
	cin >> T;
	while (T--)
	{
		int n, i, j;
		cin >> n;
		vector<int> f(n + 1, -1), pr;
		for (i = 2; i <= n; i++)
		{
			if (f[i] == -1) pr.push_back(i), f[i] = 1;
			for (int p : pr)
			{
				if (i * p > n) break;
				f[i * p] = f[i] ^ 1;
				if (i % p == 0) break;
			}
		}
		vector<int> ans;
		for (i = 2; i <= n; i++) if (f[i]) ans.push_back(i);
		ans.resize(n / 2);
		cout << ans << '\n';
	}
}
