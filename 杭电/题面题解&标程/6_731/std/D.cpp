#include <bits/stdc++.h>
//using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ld long double
using namespace std;
#define ar array
#define ll long long
#define pb push_back
#define eb emplace_back
#define idt int t; cin >> t;
#define idn int n; cin >> n;
#define pii pair<int, int>
#define iii array<int,3>
#define se10 setprecision(10) <<
#define fi fixed <<
#define all(cont) cont.begin(),cont.end()
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define Fd(i,x,y) for(int i = (x); i >= (y); i--)
#define len(x) ((ll)(x).size())
#define int long long
const int iinf = 1e18;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
const int mod = 998244353;
#ifdef LOCAL
#include "debug_util.h"
#else
#define debug(...)
#define debugArr(...)
#define io
#endif
int dr[] = {1, -1, 0, 0};int dc[] = {0, 0, 1, -1};
template<class T>
bool constexpr cmin(T &a, T b) {if (a > b) {a = b;return true;}return false;}
template<class T>
bool constexpr cmax(T &a, T b) {if (a < b) {a = b;return true;}return false;}


const int N = 1e6 + 7;
struct mint {
    int x;
    inline mint(int o = 0) { x = o; }
    inline mint & operator = (int o) { return x = o, *this; }
    inline mint & operator += (mint o) { return (x += o.x) >= mod && (x -= mod), *this; }
    inline mint & operator -= (mint o) { return (x -= o.x) < 0 && (x += mod), *this; }
    inline mint & operator *= (mint o) { return x = (ll) x * o.x % mod, *this; }
    inline mint & operator ^= (int b) {
        mint w = *this;
        mint ret(1);
        for(; b; b >>= 1, w *= w) if(b & 1) ret *= w;
        return x = ret.x, *this;
    }
    inline mint & operator /= (mint o) { return *this *= (o ^= (mod - 2)); }
    friend inline mint operator + (mint a, mint b) { return a += b; }
    friend inline mint operator - (mint a, mint b) { return a -= b; }
    friend inline mint operator * (mint a, mint b) { return a *= b; }
    friend inline mint operator / (mint a, mint b) { return a /= b; }
    friend inline mint operator ^ (mint a, int b) { return a ^= b; }
};
inline mint qpow(mint x, int y = mod - 2) { return x ^ y; }
mint fac[N], ifac[N], inv[N];
void init(int x) {
    fac[0] = ifac[0] = inv[1] = 1;
    F(i, 2, x) inv[i] = (mod - mod / i) * inv[mod % i];
    F(i, 1, x) fac[i] = fac[i - 1] * i, ifac[i] = ifac[i - 1] * inv[i];
} 
mint C(int x, int y) {
    return x < y || y < 0 ? 0 : fac[x] * ifac[y] * ifac[x - y];
}
inline mint sgn(int x) {
    return (x & 1) ? mod - 1 : 1;
}
int n, m, v[N], a[N], b[N], c[N];
vector<int> adj[N];
void solve() {
    cin >> n >> m;
    //C(n^2 - n + m, m)
    mint tt = mint(n) * mint(n - 1);
    mint num = 1;
    F(i, 1, m) num *= mint(tt + i);
    num *= ifac[m];
    cout << num.x << "\n";
}

signed main() {
    cin.tie(0);ios_base::sync_with_stdio(0); io;
    int t = 1;
    init(6e5);
    //cin >> t;   
    while(t--){solve();}
    return 0;
}