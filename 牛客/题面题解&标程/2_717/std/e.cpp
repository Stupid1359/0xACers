#include <bits/stdc++.h>
#pragma GCC optimize("O3,Ofast,unroll-loops")

using namespace std;
typedef long long ll;
 
const int M = 1e7;
bool notPrime[M + 1];
int primes[M], pt = 0;
 
void sieve() {
    for (int i = 2; i <= M; i ++) {
        if (!notPrime[i]) {
            primes[pt ++] = i;
            for (int j = i * 2; j <= M; j += i) {
                notPrime[j] = 1;
            }
        }
    }
}
 
const int N = 100000;
int p1, vt, z[N + 5], pr[N + 5];
ll n, x, v[N + 5], f[2][N + 5], s[N + 5], g[N + 5];
 
void reset() {
    p1 = 0;
    vt = 0;
    x = 0;
    for (int i = 0; i <= N; i ++) {
        z[i] = 0, pr[i] = 0;
        v[i] = 0, f[0][i] = 0, f[1][i] = 0, s[i] = 0, g[i] = 0;
    } 
}
 
void min25_sieve()
{
    for (int i = 2; i <= N; i++)
    {
        if (!z[i])
        {
            pr[++p1] = i;
            s[p1] = p1;
        }
        for (int j = 1; j <= p1 && i * pr[j] <= N; j++)
        {
            z[i * pr[j]] = 1;
            if (i % pr[j] == 0)
                break;
        }
    }
}
 
void init()
{
    x = sqrt(n) + 1;
    min25_sieve();
    for (ll l = 1, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        v[++vt] = n / l;
        if (n / l <= x)
            f[0][n / l] = vt;
        else
            f[1][l] = vt;
        ll t = n / l;
        g[vt] = t - 1;
    }
    ll w;
    for (int i = 1; i <= p1; i++)
    {
        w = 1ll * pr[i] * pr[i];
        ll t;
        for (int j = 1; j <= vt && w <= v[j]; j++)
        {
            t = v[j] / pr[i];
            if (t <= x)
                t = f[0][t];
            else
                t = f[1][n / t];
            g[j] -= g[t] - s[i - 1];
        }
    }
}
 
ll S(ll p, int q)
{
    if (pr[q] >= p)
        return 0;
    ll td = (p <= x ? f[0][p] : f[1][n / p]);
    ll re = g[td] - s[q];
    return re;
}
 
ll count(int x) {
    ll ans = 0;
    for (int i = 0; i < pt; i ++)
        ans += x / primes[i];
 
    n = x;
    reset();
    init();
 
    for (int i = 1; i <= 100; i ++) {
        if (x / i > M) {
            ans += S(x / i, 0) - pt;
        }
    }
 
    return ans;
}
 
ll solve(ll x) {
    ll ans = 0;
 
    int l = 0, r = 1e9;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (1ll * mid * mid <= x) l = mid + 1;
        else r = mid - 1;
    }
 
    ans += count(r);
 
    int tmp = r + 1;
 
    for (int i = 2; i <= 100000; i ++) {
        if (tmp % i == 0) {
            if (1ll * (r + 1) * (r + 1) - i <= x)
                ans ++;
            while (tmp % i == 0)
                tmp /= i;
        }
    }
 
    if (tmp > 1 && 1ll * (r + 1) * (r + 1) - tmp <= x)
        ans ++;
 
    return ans;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    sieve();
 
    ll l, r;
    cin >> l >> r;
 
    cout << solve(r) - solve(l - 1);
 
    return 0;
}
