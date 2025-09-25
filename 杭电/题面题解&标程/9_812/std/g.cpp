#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int Mod = 998244353;
const int M = 1e6 + 10;
int n, p[M], fac[M], ifac[M], st[M], top, son[M][2], ans = 1;

int poww(int a, int b = Mod - 2) {
    int res = 1;
    while(b) {
        if (b & 1) res = res * a % Mod;
        a = a * a % Mod, b >>= 1;
    }
    return res;
}



void init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % Mod;
    ifac[n] = poww(fac[n]);
    for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % Mod;
}

int C(int m, int n) {
    if (m < n || n < 0) return 0;
    return fac[m] * ifac[n] % Mod * ifac[m - n] % Mod;
}

void work(int p, int l, int r, int dep = 1) {
    int lst = r - l;
    //lst dep
    ans = (ans + C(lst + dep, dep)) % Mod;
    if (son[p][0]) work(son[p][0], l, p - 1, dep + 1);
    if (son[p][1]) work(son[p][1], p + 1, r, dep + 1);
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= n; i++) {
        while(top != 0 && p[st[top]] > p[i]) son[i][0] = st[top], top--;
        if (top) son[st[top]][1] = i;
        st[++top] = i;
    }
    int rt = st[1];
    work(rt, 1, n);
    cout << ans << '\n';
}

void clear() {
    top = 0; ans = 1;
    for (int i = 1; i <= n; i++) st[i] = son[i][0] = son[i][1] = 0;
}

signed main() {
    cin.sync_with_stdio(false), cin.tie(0);
    init(1e6);
    int T; cin >> T;
    while(T--) solve(), clear();
    return 0;
}