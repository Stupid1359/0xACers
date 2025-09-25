#pragma GCC optimize(2,3,"inline","Ofast","unroll-loops")
#include<bits/stdc++.h>
#define M 19000005
#define mod 1000000007
using namespace std;
int mul[M], inv[M], gv[30], seq[M], tot;
int qpow(int x, int ti)
{
    int ret = 1;
    while(ti)
    {
        if(ti & 1) ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        ti >>= 1;
    }
    return ret;
}
void init()
{
    for(int i = 1; i <= 23; i++) gv[i] = qpow(1 << i, mod - 2);
    mul[0] = 1;
    for(int i = 1; i < M; i++) mul[i] = 1ll * mul[i - 1] * i % mod;
    inv[M - 1] = qpow(mul[M - 1], mod - 2);
    for(int i = M - 2; i >= 0; i--) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
}
inline int C(int x, int y)
{
    return 1ll * mul[x] * inv[y] % mod * inv[x - y] % mod;
}
int gS(int n, int m, int k)
{
    int bd = min(n / k, 1 << m), ret = 0, w = (1 << m) - 1;
    tot = 0;
    for(int i = 0; i <= bd; i++)
    {
    	int ww = C(1 << m, i);
    	seq[tot++] = ww;
        int xx = 1ll * C(n - i * k + w, w) * ww % mod;
        if(i & 1)
        {
            ret -= xx;
            if(ret < 0) ret += mod;
        }
        else
        {
            ret += xx;
            if(ret >= mod) ret -= mod;
        }
    }
    return ret;
}
int gW0(int n, int m, int k)
{
    n /= 2;
    m--;
    int bd = min(n / k, 1 << m), ret = 0, w = (1 << m) - 1;
    for(int i = 0; i <= bd; i++)
    {
        int xx = 1ll * C(n - i * k + w, w) * C(1 << m, i) % mod;
        if(i & 1)
        {
            ret -= xx;
            if(ret < 0) ret += mod;
        }
        else
        {
            ret += xx;
            if(ret >= mod) ret -= mod;
        }
    }
    return ret;
}
int gW1(int n, int m, int k)
{
    n /= 2;
    int s = (k + 1) / 2;
    int bd = min(n / s, 1 << m), ret = 0, w = (1 << m - 1) - 1;
    for(int i = 0; i <= bd; i++)
    {
        int xx = 1ll * C(n - i * s + w, w) * seq[i] % mod;
        if(i & 1)
        {
            ret -= xx;
            if(ret < 0) ret += mod;
        }
        else
        {
            ret += xx;
            if(ret >= mod) ret -= mod;
        }
    }
    return ret;
}
int calc(int n, int m, int k)
{
    int S = gS(n, m, k + 1), iv = gv[m];
    if(n & 1) return 1ll * S * iv % mod;
    int W;
    if(k & 1) W = gW1(n, m, k);
    else W = gW0(n, m, k + 1);
    if(S < W) S += mod;
    S -= W;
    return (1ll * S * iv + W) % mod;
}
void solveA()
{
    int n, m, k;
    cin >> n >> m >> k;
    cout << calc(n, m, k) << '\n';
}
void solveB()
{
    int n, m;
    cin >> n >> m;
    int xorn = 0, sum = 0;
    for(int k = 1; k <= n; k++)
    {
    	int w = calc(n, m, k);
        xorn ^= w;
        sum = (sum + 1ll * w * w) % mod;
		if(sum > mod) sum -= mod; 
    }
    cout << xorn << ' ' << sum << '\n';
}
signed main()
{
//    freopen("xordt.in", "r", stdin);
//    freopen("xordt2.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); 
    init();
    int T;
    cin >> T;
    while(T--)
    {
        solveA();
        solveB();
    }
    return 0;
}
