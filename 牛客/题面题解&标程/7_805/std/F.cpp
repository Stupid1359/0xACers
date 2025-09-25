#include "bits/stdc++.h"
using namespace std;
const int p = 998244353;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, x, i, c = 0;
	cin >> n;
	for (i = 0; i < n; i++) cin >> x, c += x & 1;
	cout << c * (n - c + 0ll) % p << endl;
}
