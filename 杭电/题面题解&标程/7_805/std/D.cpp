#include "bits/stdc++.h"
using namespace std;
using db = long double;
template<class T1, class T2> bool cmin(T1 &x, const T2 &y) { if (y < x) { x = y; return 1; } return 0; }
template<class T1, class T2> bool cmax(T1 &x, const T2 &y) { if (x < y) { x = y; return 1; } return 0; }
#define all(x) (x).begin(),(x).end()
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(15);
	int n, m, i, j, k;
	cin >> n >> m;
	vector reach(n, vector<int>(n));
	vector<tuple<int, int, int>> eg(m);
	int W = 0;
	for (auto &[u, v, w] : eg)
	{
		cin >> u >> v >> w;
		reach[--u][--v] = 1;
		cmax(W, w);
	}
	for (k = 0; k < n; k++) for (i = 0; i < n; i++) for (j = 0; j < n; j++) reach[i][j] |= reach[i][k] & reach[k][j];
	vector f(n, vector(n, vector<int>(W * n + 1, 1e9))), g(f);
	for (i = 0; i < n; i++) f[i][i][0] = 0;
	db ans = 1e18;
	for (int step = 1; step <= n; step++)
	{
		for (auto &v : g) for (auto &vv : v) fill(all(vv), 1e9);
		for (i = 0; i < n; i++) for (auto [u, v, w] : eg) for (j = 0; j <= W * (step - 1); j++) cmin(g[i][v][j + w], f[i][u][j] + w * w);
		swap(f, g);
		for (j = 0; j <= W * step; j++) if (f[0][n - 1][j] != 1e9) cmin(ans, (db)(f[0][n - 1][j] * step - j * j) / (step * step));
		for (i = 0; i < n; i++) for (j = 0; j <= W * step; j++) if (f[i][i][j] != 1e9 && reach[0][i] && reach[i][n - 1]) cmin(ans, (db)(f[i][i][j] * step - j * j) / (step * step));
	}
	if (ans == 1e18) cout << "-1\n";
	else cout << ans << endl;
}
