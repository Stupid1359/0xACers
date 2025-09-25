#include "bits/stdc++.h"
#include "testlib.h"
using namespace std;
const int N = 1e6 + 6;
vector<int> pr;
int mn[N], mp[N];
int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);
	{
		int n = N - 1, i;
		for (i = 2; i <= n; i++)
		{
			if (!mn[i]) pr.push_back(mn[i] = i);
			for (int p : pr)
			{
				if (i * p > n) break;
				mn[i * p] = p;
				if (i % p == 0) break;
			}
		}
		mp[1] = 1;
		for (i = 2; i <= n; i++) mp[i] = mn[i / mn[i]] == mn[i] ? mp[i / (mn[i] * mn[i])] : mp[i / mn[i]] * mn[i];
	}
	int T;
	T = inf.readInt(1, 10'000, "T");
	for (int t = 1; t <= T; t++)
	{
		int n, i, j, d;
		setTestCase(t);
		n = inf.readInt(2, 1'000'000, "n");
		vector<int> ed(n + 1), med(n + 1);
		for (i = 0; i < n / 2; i++)
		{
			int x = ouf.readInt(1, n, "si");
			if (exchange(ed[x], 1)) ouf.quitf(_wa, "Duplicated number %d", x);
			med[mp[x]] = x;
		}
		vector<pair<int, int>> av;
		for (i = 1; i <= n; i++) if (mp[i] == i) for (j = 1; j <= i && j * i <= n; j++) if (mp[j] == j && med[i * j] && gcd(i, j) == 1) av.push_back({i, j});
		for (d = 1; d <= n; d++) if (mp[d] == d)
		{
			while (av.size() && av.back().first * d > n) av.pop_back();
			for (auto [i, j] : av) if (med[i * d] && med[j * d]) ouf.quitf(_wa, "Incorrect construct. Containing %d %d %d", med[i * j], med[i * d], med[j * d]);
		}
	}
	quitf(_ok, "Accepted");
}
