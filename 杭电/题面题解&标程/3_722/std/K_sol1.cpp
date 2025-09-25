#include <bits/stdc++.h>

constexpr int MOD = 998'244'353;
inline void add(int &x, int y) { (x += y) >= MOD && (x -= MOD); }
inline int sump(int x, int y) { return (x += y) < MOD ? x : x - MOD; }
inline int qpow(int a, int x) { int res = 1; for (; x; x >>= 1, a = 1ll * a * a % MOD) if (x & 1) res = 1ll * res * a % MOD; return res; }

#define MAXN 5005
int r[MAXN], pos[MAXN], lim[MAXN], det[MAXN];
int inv[MAXN], frac[MAXN], coef[MAXN];
void init(const int N = 5'000) {
	for (int i = 0; i <= N; ++i) 
		inv[i] = qpow(std::max(i, 1), MOD - 2);
	frac[0] = 1;
	for (int i = 1; i <= N; ++i) 
		frac[i] = 1ll * frac[i - 1] * i % MOD;
}

int dp[MAXN][MAXN], ptr[MAXN], tmax[MAXN];
void solve() {
	int n, m = 0; std::cin >> n;

	for (int i = 1; i <= n; ++i) 
		det[i] = 0;
	for (int i = 1, x, pre = 0; i <= n; ++i) {
		std::cin >> x;
		if (0 < x && x < pre) { det[x] = 1; continue; }
		r[++m] = x, coef[m] = inv[i - 1], pre = std::max(pre, x);
	}
	for (int i = 1; i <= n; ++i) 
		det[i] += det[i - 1];
	for (int i = 1; i <= m; ++i) 
		r[i] -= det[r[i]];

	for (int i = 0; i <= m + 2; ++i) 
		pos[i] = 0, ptr[i] = m + 1;
	for (int i = 0; i <= m + 2; ++i) 
		for (int j = 0; j <= m + 2; ++j) 
			dp[i][j] = 0;
	lim[0] = m;
	for (int i = 1; i <= m; ++i) {
		if (r[i] != 0) 
			pos[r[i] = m - r[i] + 1] = i;
		lim[i] = std::min({lim[i - 1], r[i - 1] == 0 ? m + 1 : r[i - 1] - 1, r[i] == 0 ? m + 1 : r[i]});
	}
	for (int i = m, j = 0, b = 0; i >= 1; --i) {
		b += (r[i] == 0);
		while (pos[j + 1] >= i || (pos[j + 1] == 0 && b > 0)) 
			b -= (pos[++j] == 0);
		tmax[i] = j + 1;
	}

	for (int i = m; i >= 1; --i) {
		auto clear = [&](int j) -> void {
			ptr[j] = i;
		};
		auto transition = [&](int j, int k) -> void {
			while (ptr[j] > i + 1 && tmax[ptr[j]] < k) --ptr[j];
			add(dp[i][k], sump(dp[i + 1][j], MOD - dp[ptr[j] + 1][j]));
		};
		if (r[i] != 0) {
			if (r[i] == 1) {
				dp[i][1] = 1;
			} else {
				for (int k = lim[i] - 1, bound = m; k > 0; --k) {
					if (pos[k] != 0) bound = std::min(bound, pos[k]);
					for (int t = i + 1; t <= bound; ++t) if (tmax[t] >= lim[i]) 
						add(dp[i][lim[i]], sump(dp[t][k], MOD - dp[t + 1][k])); else break;
				}
				clear(lim[i] - 1);
			}
		} else {
			for (int j = 1, lst = 0; j <= lim[i]; ++j) if (pos[j] == 0) {
				if (lst > 0) transition(lst, j);
				if (lst != j - 1) transition(j - 1, j);
				lst = j;
			}
			if (pos[1] == 0) add(dp[i][1], 1);
		}
		for (int j = 1; j <= lim[i]; ++j) if (pos[j] == 0 || pos[j] == i) 
			dp[i][j] = 1ll * dp[i][j] * coef[i] % MOD;
		if (i == 1) 
			std::cout << (std::accumulate(dp[i] + 1, dp[i] + lim[1] + 1, 0ll) % MOD * frac[n - 1] % MOD) << '\n';
		for (int j = 1; j <= lim[i]; ++j) 
			add(dp[i][j], dp[i + 1][j]);
	}
}

int main() { int t; std::cin >> t; init(); while (t--) solve(); return 0; }