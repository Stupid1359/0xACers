// Vanity Overriding Wisdom.
 
#include <bits/stdc++.h>
 
namespace FastIO {
	int fastio_digit[67], fastio_len = 0;
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= (ch == '-'), ch = getchar(); while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar(); return w ? -x : x; }
	template <typename T> inline void write(T x) { if (!x) return (void)putchar('0'); while (x) fastio_digit[++fastio_len] = x % 10, x /= 10; while (fastio_len > 0) putchar(fastio_digit[fastio_len--] ^ '0'); }
	template <typename T> inline void print(T x) { if (x >= 0) write<T>(x); else putchar('-'), write<T>(-x); }
	template <typename T> inline void print(T x, char en) { print<T>(x), putchar(en); }
}; using namespace FastIO;
 
constexpr int MOD = 998'244'353;
inline int redc(int x) { return std::min<unsigned>(x, x - MOD); }
inline void madd(int &x, int y) { x = redc(x + y); }
 
#define MAXN 5005
int p[MAXN], nxt[MAXN], cnt[MAXN], vis[MAXN], f[MAXN][MAXN];
void solve() {
	int n = read<int>();
	for (int i = 1; i <= n; ++i) 
		vis[i] = cnt[i] = 0;
	for (int i = 1; i <= n; ++i) 
		p[i] = read<int>(), vis[p[i]] = i;
	nxt[n + 1] = n + 1;
	for (int i = n; i >= 1; --i) 
		nxt[i] = vis[i] > 0 ? nxt[i + 1] : i;
	for (int i = 1; i <= n; ++i) 
		cnt[i] = cnt[i - 1] + (vis[i] <= 1);
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j) 
			f[i][j] = 0;
	f[1][p[1] == 0 ? nxt[1] : p[1]] = 1;
	for (int i = 1; i < n; ++i) {
		if (p[i + 1] == 0) {
			for (int j = 1; j <= n; ++j) if (f[i][j] > 0) {
				madd(f[i + 1][nxt[j + 1]], f[i][j]);
				if (cnt[j] >= i + 1) madd(f[i + 1][j], 1ll * f[i][j] * i % MOD);
				else if (vis[j] == 0) madd(f[i + 1][nxt[j + 1]], 1ll * f[i][j] * i % MOD);
			}
		} else {
			for (int k = p[i + 1]; k <= n; ++k) 
				++cnt[k];
			for (int j = 1; j < p[i + 1]; ++j) if (f[i][j] > 0) {
				madd(f[i + 1][p[i + 1]], f[i][j]);
				if (vis[j] == 0) madd(f[i + 1][nxt[p[i + 1] + 1]], 1ll * f[i][j] * i % MOD);
			}
			for (int j = p[i + 1] + 1; j <= n; ++j) if (f[i][j] > 0) 
				madd(f[i + 1][j], 1ll * f[i][j] * i % MOD);
		}
	}
	print<int>(f[n][n], '\n');
}
 
int main() { int t = read<int>(); while (t--) solve(); return 0; }