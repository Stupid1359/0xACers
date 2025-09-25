#include "bits/stdc++.h"
using namespace std;
using ll = long long;
template<class T1, class T2> bool cmin(T1 &x, const T2 &y) { if (y < x) { x = y; return 1; } return 0; }
template<class T1, class T2> bool cmax(T1 &x, const T2 &y) { if (x < y) { x = y; return 1; } return 0; }
#define all(x) (x).begin(),(x).end()
const int m = 10, N = m + 3, M = 1 << N;
int f[N + 1][N + 1][M], mx[N + 1][M];
vector<int> manacher(const string &t)
{
	string S = "$#";
	int n = t.size(), i, r = 1, m = 0;
	for (i = 0; i < n; i++) S += t[i], S += '#';
	S += '#';
	char *s = S.data() + 2;
	n = n * 2 - 1;
	vector<int> ex(n);
	ex[0] = 2;
	for (i = 1; i < n; i++)
	{
		ex[i] = i < r ? min(ex[m * 2 - i], r - i + 1) : 1;
		while (s[i + ex[i]] == s[i - ex[i]]) ++ex[i];
		if (i + ex[i] - 1 > r) r = i + ex[m = i] - 1;
	}
	for (i = 0; i < n; i++) --ex[i];
	return ex;
}
struct sgt
{
	int n, shift, z, y, val, *a;
	vector<int> s;
	void build(int x, int l, int r)
	{
		if (l == r)
		{
			s[x] = a[l];
			return;
		}
		int c = x * 2, m = l + r >> 1;
		build(c, l, m); build(c + 1, m + 1, r);
		s[x] = max(s[c], s[c + 1]);
	}
	sgt(int *b, int L, int R) :n(R - L + 1), shift(L - 1), a(b + L - 1), s(R - L + 1 << 2) { build(1, 1, n); }
	void find_right_most(int x, int l, int r)
	{
		if (l > y || s[x] < val) return;
		if (l == r) { z = l;  return; }
		int c = x * 2, m = l + r >> 1;
		find_right_most(c + 1, m + 1, r);
		if (z == 0) find_right_most(c, l, m);
	}
	int find_right_most(int r, int v)
	{
		val = v; z = 0; y = r - shift;
		find_right_most(1, 1, n);
		return z + shift;
	}
};
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	{
		auto rev = [&](string s) {
			reverse(all(s));
			return s;
		};
		int i, j, k, S, op;
		for (i = 1; i <= N; i++) for (S = 0; S < 1 << i; S++)
		{
			string s(i, '0');
			for (j = 0; j < i; j++) s[j] += S >> j & 1;
			auto ex = manacher(s);
			mx[i][S] = *max_element(all(ex));
		}
		for (i = 0; i <= N; i++)
		{
			if (i)
			{
				memset(f[i], 0x3f, sizeof f[0]);
				for (j = 0; j + i <= N; j++) for (S = 0; S < 1 << j; S++)
				{
					for (op = 0; op < 2; op++)
					{
						int T = (S << 1) | op;
						cmin(f[i][j][S], f[i - 1][j + 1][T]);
					}
					cmax(f[i][j][S], mx[j][S]);
				}
			}
			for (j = 0; j + i <= N; j++) for (S = 0; S < 1 << j; S++) cmax(f[i][j][S], mx[j][S]);
		}
	}
	int T;
	cin >> T;
	while (T--)
	{
		int n, add, i, j;
		string a;
		cin >> a >> add;
		n = a.size();
		ll ans = 0;
		for (i = 0; i < n; i++)
		{
			int S = 0;
			for (j = 0; j < m && j + i < n; j++)
			{
				S = S << 1 | a[i + j] - '0';
				ans += f[min(add, N - 1 - j)][j + 1][S] - mx[j + 1][S];
			}
		}
		cmin(add, 2);
		auto ex = manacher(a);
		int sz = ex.size();
		sgt s(ex.data(), 0, sz - 1);
		int len = 0;
		for (i = 0; i < n; i++)
		{
			len = (i == 0 || a[i] == a[i - 1] ? len + 1 : 1);
			if (i >= max(m, len))//i-max(m, len)
			{
				int l = i - len + 1, r = i - max(m, len);//[l,i],ex[l+i]
				int mid = s.find_right_most(l + i - 1, len + 1);
				l = mid - len >> 1;//l+r=mid,r-l=len/len+1
				if (l >= 0)
				{
					if (l < r) ans += add * (r - l), r = l;
					if ((mid == i * 2 - len || ex[mid] == len + 1) && l)
					{
						mid = s.find_right_most(mid - 1, len + 2);
						l = max(-1, mid - len - 1 >> 1);
						if (l < r) ans += (add - 1) * (r - l);
					}
					else if ((ex[mid] - len & 1) && l == r) ans += add - 1;
				}
				else ans += add * (r + 1);
			}
		}
		cout << ans << '\n';
	}
}
