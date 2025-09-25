#include "bits/stdc++.h"
using namespace std;
using ll = long long;
#define all(x) (x).begin(),(x).end()
template<class info, class tag> struct sgt
{
	int n, shift;
	info tmp;
	vector<info> s;
	vector<tag> tg;
	vector<int> lz;
	bool flg;
	void build(int x, int l, int r)
	{
		if (l == r)
		{
			s[x] = tmp;
			return;
		}
		int c = x * 2, m = l + r >> 1;
		build(c, l, m); build(c + 1, m + 1, r);
		s[x] = s[c] + s[c + 1];
	}
	sgt(info b, int L, int R) :n(R - L + 1), shift(L - 1), s(R - L + 1 << 2), tg(R - L + 1 << 2), lz(R - L + 1 << 2)
	{
		tmp = b;
		build(1, 1, n);
	}
	int z, y;
	info res;
	tag dt;
	bool fir;
private:
	void _modify(int x, int l, int r)
	{
		if (z <= l && r <= y)
		{
			s[x] += dt;
			if (lz[x]) tg[x] += dt; else tg[x] = dt;
			lz[x] = 1;
			return;
		}
		int c = x * 2, m = l + r >> 1;
		if (lz[x])
		{
			if (lz[c]) tg[c] += tg[x]; else tg[c] = tg[x];
			lz[c] = 1; s[c] += tg[x]; c ^= 1;
			if (lz[c]) tg[c] += tg[x]; else tg[c] = tg[x];
			lz[c] = 1; s[c] += tg[x]; c ^= 1;
			lz[x] = 0;
		}
		if (z <= m) _modify(c, l, m);
		if (m < y) _modify(c + 1, m + 1, r);
		s[x] = s[c] + s[c + 1];
	}
	void ask(int x, int l, int r)
	{
		if (z <= l && r <= y)
		{
			res = fir ? s[x] : res + s[x];
			fir = 0;
			return;
		}
		int c = x * 2, m = l + r >> 1;
		if (lz[x])
		{
			if (lz[c]) tg[c] += tg[x]; else tg[c] = tg[x];
			lz[c] = 1; s[c] += tg[x]; c ^= 1;
			if (lz[c]) tg[c] += tg[x]; else tg[c] = tg[x];
			lz[c] = 1; s[c] += tg[x]; c ^= 1;
			lz[x] = 0;
		}
		if (z <= m) ask(c, l, m);
		if (m < y) ask(c + 1, m + 1, r);
	}
public:
	void modify(int l, int r, const tag &x)
	{
		z = l - shift; y = r - shift; dt = x;
		_modify(1, 1, n);
	}
	info ask(int l, int r)
	{
		z = l - shift; y = r - shift; fir = 1;
		ask(1, 1, n);
		return res;
	}
};
struct tag
{
	int dx, dy;
	void operator+=(const tag &o) { if (o.dx != -1) dx = o.dx; if (o.dy != -1) dy = o.dy; }
};
struct info
{
	ll sxy, sx, sy, c;
	info operator+(const info &o) const { return {sxy + o.sxy, sx + o.sx, sy + o.sy, c + o.c}; }
	void operator+=(const tag &o)
	{
		if (o.dx != -1)
		{
			sx = c * o.dx;
			sxy = sy * o.dx;
		}
		if (o.dy != -1)
		{
			sy = c * o.dy;
			sxy = sx * o.dy;
		}
	}
};
template<class T> struct bit1
{
	vector<T> a;
	int n;
	bit1(int nn, T val) :n(nn), a(nn + 1, val) { }
	void update(int x, T y)
	{
		++x;
		assert(1 <= x && x <= n);
		a[x] = min(a[x], y);
		while ((x += x & -x) <= n) a[x] = min(a[x], y);
	}
	T ask(int x)
	{
		++x;
		assert(0 <= x && x <= n);
		T r = a[x];
		while (x ^= x & -x) r = min(r, a[x]);
		return r;
	}
};
template<class T> struct bit2
{
	vector<T> a;
	int n;
	bit2(int nn, T val) :n(nn), a(nn + 1, val) { }
	void update(int x, T y)
	{
		++x;
		assert(1 <= x && x <= n);
		a[x] = min(a[x], y);
		while (x ^= x & -x) a[x] = min(a[x], y);
	}
	T ask(int x)
	{
		++x;
		assert(1 <= x && x <= n);
		T r = a[x];
		while ((x += x & -x) <= n) r = min(r, a[x]);
		return r;
	}
};
const int N = 5e5 + 5;
int main()
{
	static int a[N], p[N], l[N], r[N], inc[N], dec[N], st[N];
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(15);
	int T; cin >> T;
	while (T--)
	{
		int n, m, i, j;
		cin >> n;
		a[0] = a[n + 1] = n + 1;
		for (i = 1; i <= n; i++)
		{
			cin >> a[i];
			p[a[i]] = i;
			r[i] = n + 1;
		}
		sgt<info, tag> t({0, 0, 0, 1}, 0, n + 1);
		int tp1 = 0, tp2 = 0;
		for (i = 1; i <= n; i++)
		{
			while (tp1 && a[st[tp1]] > a[i])
				r[st[tp1--]] = i;
			l[i] = st[tp1];
			st[++tp1] = i;
		}
		dec[tp1 = 0] = n + 1;
		bit1<int> b1(n + 2, n + 1);
		bit2<int> b2(n + 2, n + 1);
		ll ans = 0;
		for (i = n; i; i--)
		{
			int x = p[i];
			while (inc[tp1] > x) --tp1;
			while (dec[tp2] < x) --tp2;
			t.modify(i, a[inc[tp1]] - 1, {x, -1});
			t.modify(i, a[dec[tp2]] - 1, {-1, x});
			inc[++tp1] = dec[++tp2] = x;
			int L = l[x], R = r[x];
			int mex = min(b1.ask(L), b2.ask(R)) - 1;
			b1.update(x, i), b2.update(x, i);
			auto [sxy, sx, sy, c] = t.ask(i, mex);
			ans += L * sy + R * sx - sxy - c * L * R + 1ll * i * (R - x) * (x - L);
		}
		cout << ans << '\n';
	}
}
