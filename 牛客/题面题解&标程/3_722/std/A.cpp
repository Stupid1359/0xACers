#include <bits/stdc++.h>

namespace FastIO {
	int fastio_digit[67], fastio_len = 0;
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= (ch == '-'), ch = getchar(); while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar(); return w ? -x : x; }
	template <typename T> inline void write(T x) { if (!x) return (void)putchar('0'); while (x) fastio_digit[++fastio_len] = x % 10, x /= 10; while (fastio_len > 0) putchar(fastio_digit[fastio_len--] ^ '0'); }
	template <typename T> inline void print(T x) { if (x >= 0) write<T>(x); else putchar('-'), write<T>(-x); }
	template <typename T> inline void print(T x, char en) { print<T>(x), putchar(en); }
}; using namespace FastIO;

#define MAXN 1501
struct Node {
	int v, id;
	Node () {}
	Node (int V, int I) : v(V), id(I) {}
	const bool operator < (const Node &k) const { return v < k.v; }
} f[MAXN];

int slot[MAXN], A[MAXN][MAXN];
void solve() {
	int n = read<int>(), m = 0;
	for (int i = 1; i <= n; ++i) 
		f[i] = Node(read<int>(), i);
	std::sort(f + 1, f + n + 1);
	for (int i = 1, j = 1; j <= n; ++j) {
		while (i <= n && f[i].v < j) ++i;
		if (i > n || f[i].v > j) slot[++m] = j;
	}
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j) 
			A[i][j] = -1;
	for (int i = 1, p = 1, nxt; i <= n; ++i) {
		if (f[i].v != f[i - 1].v) {
			nxt = f[i - 1].v;
		} else {
			nxt = slot[p], p = std::min(p + 1, m);
		}
		for (int k = 1; k <= n; ++k) 
			if (A[f[i].id][k] == -1) A[f[i].id][k] = nxt;
		for (int k = 1; k <= n; ++k) 
			if (A[k][f[i].id] == -1) A[k][f[i].id] = nxt;
	}
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j) 
			print<int>(A[i][j], " \n"[j == n]);
}

int main() { int t = read<int>(); while (t--) solve(); return 0; }