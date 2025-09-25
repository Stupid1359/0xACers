#include "bits/stdc++.h"
using namespace std;
template<typename T> struct sgt
{
	int L, R;
	vector<int> l, r, ys;
	vector<T> a, plz, mx, mn;
	int z, y;
	T dt;
	void pushup(int x)
	{
		int c = x * 2;
		mx[x] = max(mx[c], mx[c + 1]);
		mn[x] = min(mn[c], mn[c + 1]);
	}
	void plus(int x, T y)
	{
		plz[x] += y;
		mx[x] += y;
		mn[x] += y;
	}
	void pushdown(int x)
	{
		int c = x * 2;
		if (plz[x])
		{
			plus(c, plz[x]); plus(c + 1, plz[x]);
			plz[x] = 0;
		}
	}
	void build(int x)
	{
		plz[x] = 0;
		if (l[x] == r[x])
		{
			ys[l[x]] = x;
			mx[x] = a[l[x]];
			mn[x] = a[l[x]];
			return;
		}
		int c = x * 2;
		l[c] = l[x]; r[c] = l[x] + r[x] >> 1;
		l[c + 1] = r[c] + 1; r[c + 1] = r[x];
		build(c); build(c + 1);
		pushup(x);
	}
	void init(int n)
	{
		a.resize(n + 1);
		ys.resize(n + 1);
		n <<= 2;
		l.resize(n);
		r.resize(n);
		plz.resize(n);
		mx.resize(n);
		mn.resize(n);
	}
	template<typename TT> sgt(TT *b, int lt, int rt)
	{
		assert(lt <= rt);
		L = lt; R = rt; init(R - L + 1);
		for (int i = L; i <= R; i++) a[i - L + 1] = b[i];
		r[l[1] = 1] = R - L + 1; build(1);
	}
	void modify_plus(int x)
	{
		if (z <= l[x] && r[x] <= y)
		{
			plus(x, dt);
			return;
		}
		int c = x * 2;
		pushdown(x);
		if (z <= r[c]) modify_plus(c);
		if (y > r[c]) modify_plus(c + 1);
		pushup(x);
	}
	void modify_plus(int l, int r, T x)
	{
		assert(L <= l && l <= r && r <= R);
		dt = x; z = l - L + 1; y = r - L + 1;
		modify_plus(1);
	}
	void ask_max(int x)
	{
		if (z <= l[x] && r[x] <= y)
		{
			dt = max(dt, mx[x]);
			return;
		}
		pushdown(x);
		int c = x * 2;
		if (z <= r[c]) ask_max(c);
		if (y > r[c]) ask_max(c + 1);
	}
	T ask_max(int l, int r)
	{
		assert(L <= l && l <= r && r <= R);
		z = l - L + 1; y = r - L + 1; dt = numeric_limits<T>::min();
		ask_max(1);
		return dt;
	}
	void ask_min(int x)
	{
		if (z <= l[x] && r[x] <= y)
		{
			dt = min(dt, mn[x]);
			return;
		}
		pushdown(x);
		int c = x * 2;
		if (z <= r[c]) ask_min(c);
		if (y > r[c]) ask_min(c + 1);
	}
	T ask_min(int l, int r)
	{
		assert(L <= l && l <= r && r <= R);
		z = l - L + 1; y = r - L + 1; dt = numeric_limits<T>::max();
		ask_min(1);
		return dt;
	}
};
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, q, i;
	string s;
	cin >> n >> q >> s;
	vector<int> a(n + 1);
	for (i = 0; i < n; i++) a[i + 1] = a[i] + (s[i] == 'A' ? 1 : -1);
	s = ' ' + s;
	sgt<int> t(a.data(), 0, n);
	while (q--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int x;
			cin >> x;
			t.modify_plus(x, n, s[x] == 'A' ? -2 : 2);
			s[x] ^= 'A' ^ 'B';
		}
		else
		{
			int l, r;
			cin >> l >> r; --l;
			int shift = t.ask_max(l, l), pre_max = t.ask_max(l + 1, r), pre_min = t.ask_min(l + 1, r), pre = t.ask_max(r, r);
			pre_max -= shift; pre_min -= shift; pre -= shift;
			if (pre == r - l) cout << "Bob\n";
			else if (pre == l - r) cout << "Alice\n";
			else
			{
				int d = pre_max + pre_min - pre, r_max = t.ask_max(l + pre_max + 1, r) - shift, r_min = t.ask_min(l - pre_min + 1, r) - shift;
				cout << (d < 0 ||
					d == 1 && pre_max != r_max ||
					d == 0 && pre_min == r_min ? "Alice\n" : "Bob\n");
			}
		}
	}
}
