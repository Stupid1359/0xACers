#include <bits/stdc++.h>

using i32 = int32_t;
using u32 = uint32_t;
using u64 = uint64_t;
template <uint32_t MOD> struct mint {
	static constexpr u32 get_r() {
		u32 ret = MOD;
		for (i32 i = 0; i < 4; ++i) ret *= 2 - MOD * ret;
		return ret;
	}
	static constexpr u32 r = get_r();
	static constexpr u32 n2 = -u64(MOD) % MOD;
	static_assert(r * MOD == 1, "invalid, r * MOD != 1");
	static_assert(MOD < (1 << 30), "invalid, MOD >= 2 ^ 30");
	static_assert((MOD & 1) == 1, "invalid, MOD % 2 == 0");
	u32 a;
	constexpr mint() : a(0) {}
	constexpr mint(const int64_t &b) : a(reduce(u64(b % MOD + MOD) * n2)){};
	static constexpr u32 reduce(const u64 &b) { return (b + u64(u32(b) * u32(-r)) * MOD) >> 32; }
	constexpr mint &operator += (const mint &b) { if (i32(a += b.a - 2 * MOD) < 0) a += 2 * MOD; return *this; }
	constexpr mint &operator -= (const mint &b) { if (i32(a -= b.a) < 0) a += 2 * MOD; return *this; }
	constexpr mint &operator *= (const mint &b) { a = reduce(u64(a) * b.a); return *this; }
	constexpr mint &operator /= (const mint &b) { *this *= b.inverse(); return *this; }
	constexpr mint operator + (const mint &b) const { return mint(*this) += b; }
	constexpr mint operator - (const mint &b) const { return mint(*this) -= b; }
	constexpr mint operator * (const mint &b) const { return mint(*this) *= b; }
	constexpr mint operator / (const mint &b) const { return mint(*this) /= b; }
	constexpr bool operator == (const mint &b) const { return (a >= MOD ? a - MOD : a) == (b.a >= MOD ? b.a - MOD : b.a); }
	constexpr bool operator != (const mint &b) const { return (a >= MOD ? a - MOD : a) != (b.a >= MOD ? b.a - MOD : b.a); }
	constexpr mint operator-() const { return mint() - mint(*this); }
	constexpr mint pow(u64 n) const { mint ret(1), mul(*this); while (n > 0) { if (n & 1) ret *= mul; mul *= mul, n >>= 1; } return ret; }
	constexpr mint inverse() const { return pow(MOD - 2); }
	friend std::ostream &operator<< (std::ostream &os, const mint &b) { return os << b.get(); }
	friend std::istream &operator>> (std::istream &is, mint &b) { int64_t t; is >> t; b = mint<MOD>(t); return (is); }
	constexpr u32 get() const { u32 ret = reduce(a); return ret >= MOD ? ret - MOD : ret; }
	static constexpr u32 get_MOD() { return MOD; }
	explicit operator u32() const { return get(); }
}; using modint = mint<998244353>;

#define MAXM 505
#define MAXV 505
modint f[2][MAXM][MAXV][2], coefL[2][MAXV], coefR[MAXV];
int o[MAXM], l[MAXM], r[MAXM], lim[MAXM];
void solve() {
	int m, v, p = 0, st = 1; std::cin >> m >> v;
	for (int i = 1, cnt = 0; i <= m; ++i) {
		std::cin >> o[i], p += (o[i] == 1 ? 1 : -1);
		if (o[i] == 1) 
			++cnt, std::cin >> l[i] >> r[i];
		lim[i] = cnt;
		if (p == 0) st = i + 1, cnt = 0;
	}
	if (st == m + 1) return (void)puts("1");
	for (int i = m, cnt = 0; i >= st; --i) 
		lim[i] = std::min(cnt, lim[i]), cnt += (o[i] == 2);
	for (int i : {0, 1}) 
		for (int k = 0; k <= m; ++k)
			for (int r = 1; r <= v; ++r) 
				f[i][k][r][0] = f[i][k][r][1] = 0;
	for (int x = 0; x <= v + 1; ++x) 
		coefL[0][x] = coefL[1][x] = coefR[x] = 0;
	for (int r = 1; r <= v; ++r) 
		f[0][0][r][0] = 1;
	auto lst = f[0], now = f[1];
	for (int i = st; i <= m; ++i) {
		if (o[i] == 1) {
			for (int k = 0; k <= lim[i]; ++k)
				for (int r = 1; r <= v; ++r) 
					now[k][r][0] = now[k][r][1] = 0;
			for (int x = v; x >= 1; --x) 
				coefR[x] = modint(l[i] <= x && x <= r[i] ? x : 0) + coefR[x + 1];
			for (int e : {0, 1}) for (int x = 1; x <= v; ++x) 
				coefL[e][x] = coefL[e][x - 1] + modint(l[i] <= x - e && x - e <= r[i] ? 1 : 0);
			for (int k = 0, b = std::min(lim[i], lim[i - 1]); k <= b; ++k) 
				for (int r = 1; r <= ::r[i]; ++r) 
					for (int e : {0, 1}) 
						now[k][r][e] += lst[k][r][e] * coefR[r];
			for (int k = 0, b = std::min(lim[i] - 1, lim[i - 1]); k <= b; ++k) 
				for (int r = l[i]; r <= v; ++r) 
					for (int e : {0, 1}) 
						now[k + 1][r][e] += lst[k][r][e] * coefL[e][r];
			for (int k = 0; k <= lim[i]; ++k) 
				for (int r = l[i]; r <= ::r[i]; ++r) 
					now[k][r][0] -= lst[k][r][0] * modint(r),
					now[k][r][1] += lst[k][r][0] * modint(r);
			std::swap(now, lst);
		} else {
			for (int k = 0; k <= lim[i]; ++k) 
				for (int r = 1; r <= v; ++r) 
					for (int e : {0, 1}) 
						lst[k][r][e] = lst[k + 1][r][e];
			modint sum = 0;
			for (int r = v; r >= 1; --r) 
				lst[0][r][0] = sum, sum += lst[0][r][1];
		}
	}
	modint ans = 0;
	for (int r = 1; r <= v; ++r) 
		ans += lst[0][r][1];
	for (int i = st; i <= m; ++i) if (o[i] == 1)
		ans *= modint(r[i] - l[i] + 1).inverse();
	std::cout << ans << '\n';
}

int main() { int t; std::cin >> t; while (t--) solve(); return 0; }