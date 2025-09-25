// Start coding: 13:30
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define ll long long
const ll mod = 998244353;
ll qpow(ll a, ll b) {
    ll ret = 1;
    while(b) {
        if(b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}

ll n, ans = 0;
string s;

int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
vector<int> i2v(int x, int n) {
    vector<int> vec;
    for(int i=0;i<n;i++) vec.push_back(x % 10), x /= 10;
    return vec;
}
int ch[1005][10], tot = 1, leaf[1005];
vector<int> trans[10];
void ins(vector<int> vec) {
    int now = 1;
    for(int i=0;i<4;i++) {
        if(!ch[now][vec[i]]) ch[now][vec[i]] = ++tot;
        now = ch[now][vec[i]];
    }
    leaf[now] = 1;
}

ll fac[MAXN], inv[MAXN];
ll C(ll n, ll m) {
    if(n < m) return 0;
    return fac[n] * inv[m] % mod * inv[n-m] % mod;
}
void init() {
    for(int i=1;i<=12;i++) for(int j=1;j<=days[i];j++) ins(i2v(i * 100 + j, 4));
    for(int i=1;i<=tot;i++) for(int j=0;j<=9;j++) if(ch[i][j]) trans[j].push_back(i);
    fac[0] = 1;
    for(int i=1;i<=n;i++) fac[i] = fac[i-1] * i % mod;
    inv[n] = qpow(fac[n], mod-2);
    for(int i=n;i>=1;i--) inv[i-1] = inv[i] * i % mod;
}
void solve1() {
    static ll pre[MAXN];
    static ll dp[MAXN][805];
    memset(dp, 0, sizeof(dp)), memset(pre, 0, sizeof(pre));
    dp[n+1][1] = 1; pre[0] = 0;
    for(int i=1;i<=n;i++) pre[i] = pre[i-1] + (s[i] == 0);
    for(int i=n;i>=5;i--) {
        for(int j=1;j<=tot;j++) dp[i][j] = dp[i+1][j];
        int c = s[i];
        for(auto j : trans[c]) (dp[i][ch[j][c]] += dp[i+1][j]) %= mod;
        ll sum = 0;
        for(int j=1;j<=tot;j++) if(leaf[j]) (sum += dp[i][j] + mod - dp[i+1][j]) %= mod;  
        (ans += (C(i-1, 4) - C(pre[i-1], 4) + mod) * sum) %= mod;
        // printf("i = %d, ans = %lld, sum = %lld\n", i, ans, sum);
    }
}
void solve2() {
    static ll f[10], suf[MAXN][5], pre[MAXN][2];
    memset(suf, 0, sizeof(suf)), memset(f, 0, sizeof(f));
    suf[n+1][0] = 1;
    for(int i=n;i>=1;i--) {
        for(int j=0;j<5;j++) suf[i][j] = suf[i+1][j];
        if(s[i] == 9) (suf[i][1] += suf[i+1][0]) %= mod;
        if(s[i] == 2) (suf[i][2] += suf[i+1][1]) %= mod, (suf[i][3] += suf[i+1][2]) %= mod;
        if(s[i] == 0) (suf[i][4] += suf[i+1][3]) %= mod;
    }
    for(int i=3;i<=n;i++) {
        ll sum = 0;
        for(int j=0;j<=9;j++) 
            if((j * 10 + s[i]) % 4 == 0 && (j != 0 || s[i] != 0)) 
                (sum += f[j]) %= mod;
        (f[s[i]] += C(i-1, 2)) %= mod;
        (ans += sum * suf[i+1][4]) %= mod;
    }
    memset(pre, 0, sizeof(pre)), memset(f, 0, sizeof(f));
    ll sum = 0;
    for(int i=1;i<=n;i++) {
        pre[i][0] = pre[i-1][0];
        if(s[i] == 0) {
            pre[i][1] = pre[i-1][0];
            (pre[i][0] += sum) %= mod;
        }
        for(int j=0;j<=9;j++) 
            if((j * 10 + s[i]) % 4 == 0 && (j != 0 || s[i] != 0)) 
                (sum += f[j]) %= mod;
        (f[s[i]] += 1) %= mod;
        (ans += pre[i][1] * suf[i+1][4]) %= mod;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin>>n;
    cin>>s; 
    s = " " + s;
    for(auto& c : s) c -= '0';
    // mt19937 rd(998244353);
    // n = 1e5; s.push_back(' ');
    // for(int i=0;i<n;i++) s.push_back(rd() % 10);
    
    init();
    solve1();
    solve2();

    cout << ans << '\n';

    return 0;
}