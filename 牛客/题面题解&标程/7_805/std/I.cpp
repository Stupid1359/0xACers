#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 32, mod = 998244353;
ll qpow(ll x, ll y = mod - 2)
{
	ll r = 1;
	for (; y; y >>= 1)
	{
		if (y & 1) r = r * x % mod;
		x = x * x % mod;
	}
	return r;
}
ll n;
int k, x;
struct mat {
	ll a[N][N];
	mat(int op = 0) {
		memset(a, 0, sizeof(a));
		if (op) for (int i = 0; i < N; ++i) a[i][i] = 1;
	}
	inline ll *operator [] (int i) { return a[i]; }
	inline const ll *operator [] (int i) const { return a[i]; }
	inline mat operator * (const mat &b) const {
		mat c;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				for (int k = 0; k < N; ++k)
					c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
		return c;
	}
};
struct vec {
	ll a[N];
	vec() { memset(a, 0, sizeof(a)); }
	inline ll &operator [] (int i) { return a[i]; }
	inline vec operator * (const mat &b) const {
		vec c;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				c[i] = (c[i] + a[j] * b[j][i]) % mod;
		return c;
	}
};
mat qpow(mat x, ll y)
{
	mat r(1);
	for (; y; y >>= 1)
	{
		if (y & 1) r = r * x;
		x = x * x;
	}
	return r;
}
void solve()
{
	cin >> n >> k;
	mat T(0);
	vec v;
	for (int i = 0; i < k; ++i)
	{
		cin >> x;
		v[x]++;
		for (int j = 0; j < 16; ++j)
		{
			T[j][j + x & 15]++;
			T[j][(j + x & 15) | 16] += j + x >> 4;
			T[j | 16][(j + x & 15) | 16]++;

			T[j][j * x & 15]++;
			T[j][(j * x & 15) | 16] += j * x >> 4;
			T[j | 16][(j * x & 15) | 16] += x;

			T[j][j & x]++;

			T[j][j | x]++;
			T[j | 16][j | x | 16]++;

			T[j][j ^ x]++;
			T[j | 16][(j ^ x) | 16]++;
		}
	}
	v = v * qpow(T, n - 1);
	ll ans = 0;
	for (int i = 0; i < 16; ++i) ans = (ans + v[i] * i + v[i | 16] * 16) % mod;
	ans = ans * qpow(qpow(k), n) % mod * qpow(qpow(5), n - 1) % mod;
	cout << ans << '\n';
}
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}
