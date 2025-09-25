#include <bits/stdc++.h>

namespace FastIO {
	int fastio_digit[67], fastio_len = 0;
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= (ch == '-'), ch = getchar(); while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar(); return w ? -x : x; }
	template <typename T> inline void write(T x) { if (!x) return (void)putchar('0'); while (x) fastio_digit[++fastio_len] = x % 10, x /= 10; while (fastio_len > 0) putchar(fastio_digit[fastio_len--] ^ '0'); }
	template <typename T> inline void print(T x) { if (x >= 0) write<T>(x); else putchar('-'), write<T>(-x); }
	template <typename T> inline void print(T x, char en) { print<T>(x), putchar(en); }
}; using namespace FastIO;

const int V = 5'000'000;
using ull = unsigned long long;

std::mt19937 eng(std::chrono::steady_clock::now().time_since_epoch().count());
ull rnd(ull l = 0ull, ull r = -1ull) { return std::uniform_int_distribution<ull>(l, r)(eng); }

#define MAXN 1000001
#define MAXV ((V) + 1)
bool compose[MAXV]; ull hash[MAXV];
void sieve() {
	std::vector<int> prime;
	for (int i = 2; i <= V; ++i) {
		if (!compose[i]) prime.push_back(i), hash[i] = rnd();
		for (int j : prime) if (i * j <= V) {
			compose[i * j] = true, hash[i * j] = hash[i] ^ hash[j];
			if (i % j == 0) break;
		} else break;
	}
}

void solve() {
	int n = read<int>(); ull h = 0;
	if (n == 2) {
		int x = read<int>(), y = read<int>();
		return (void)puts(x == y ? "YES" : "NO");
	}
	for (int i = 1; i <= n; ++i) 
		h ^= hash[read<int>()];
	puts((n & 1) || h == 0 ? "YES" : "NO");
}

int main() { int t = read<int>(); sieve(); while (t--) solve(); return 0; }