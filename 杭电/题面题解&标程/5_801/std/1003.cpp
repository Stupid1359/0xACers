#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1 << 18;
const int mod = 998244353;
using arr = int[N + 5];

arr fac, ifac;
void red(int &x) { x += x >> 31 & mod; }
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int sub(int x, int y) { return (x -= y) < 0 ? x + mod : x; }
int ksm(ll x, int tp, int s = 1) {
    for (; tp; x = x * x % mod, tp >>= 1)
        if (tp & 1) s = x * s % mod;
    return s;
}

void pre_f() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[N] = ksm(fac[N], mod - 2);
    for (int i = N; i; i--) ifac[i - 1] = 1ll * ifac[i] * i % mod;
}

namespace poly_base {
int l, n, iv;
arr g;
void r_prep(int tl) {
    int i;
    l = __lg(tl - 1) + 1;
    n = 1 << l;
    g[0] = 1;
    g[n] = ksm(31, 1 << 21 - l);
    for (i = l; i; i--) g[1 << i - 1] = 1ll * g[1 << i] * g[1 << i] % mod;
    for (i = 0; i < n; i++) g[i] = 1ll * g[i & i - 1] * g[i & -i] % mod;
}
void prep(int tl) {
    n = 1 << (l = __lg(tl - 1) + 1);
    iv = mod - (mod - 1) / n;
}
void DIT(arr T) {
    int i, *t, *j, *k, v;
    for (i = n >> 1; i; i >>= 1)
        for (t = g, j = T; j != T + n; j += i << 1, ++t)
            for (k = j; k != j + i; ++k)
                v = 1ll * *t * k[i] % mod, red(k[i] = *k - v), red(*k += v - mod);
}
void DIF(arr T) {
    int i, *t, *j, *k, v;
    for (i = 1; i < n; i <<= 1)
        for (t = g, j = T; j != T + n; j += i << 1, ++t)
            for (k = j; k != j + i; ++k)
                red(v = *k + k[i] - mod), k[i] = 1ll * *t * (*k - k[i] + mod) % mod, *k = v;
    reverse(T + 1, T + n);
    for (int i = 0; i < n; i++) T[i] = 1ll * T[i] * iv % mod;
}
void NTT(arr a) { DIT(a); }
void INTT(arr a) { DIF(a); }
void NTT(arr a, arr b) {
    memcpy(b, a, n * sizeof(int));
    DIT(b);
}
void INTT(arr a, arr b) {
    memcpy(b, a, n * sizeof(int));
    DIF(b);
}
}  // namespace poly_base

namespace poly {
using namespace poly_base;
arr pa, pb, pc, pd;
#define szf sizeof(int)
void cl(arr a) { memset(a, 0, n * szf); }
void Mult(int t, arr a, arr b, arr c) {
    if (t == 1) {
        *c = 1ll * *a * *b % mod;
        return;
    }
    prep(t);
    NTT(a, c);
    NTT(b, pa);
    for (int i = 0; i < n; i++) c[i] = 1ll * c[i] * pa[i] % mod;
    INTT(c);
    cl(pa);
}
void Inv(int t, arr a, arr b) {
    if (t == 1) {
        *b = ksm(*a, mod - 2);
        return;
    }
    int i, j;
    prep(t);
    t = n;
    cl(b);
    *b = ksm(*a, mod - 2);
    for (i = 2; i <= t; i <<= 1) {
        prep(i);
        NTT(a, pb);
        NTT(b, pc);
        for (j = 0; j < i; j++) pb[j] = 1ll * pb[j] * pc[j] % mod;
        INTT(pb);
        fill(pb, pb + (i >> 1), 0);
        NTT(pb);
        for (j = 0; j < i; j++) pb[j] = 1ll * (mod - pb[j]) * pc[j] % mod;
        INTT(pb);
        j = i >> 1;
        memcpy(b + j, pb + j, j * szf);
    }
    cl(pb);
    cl(pc);
}
void Inv2(int t, arr a, arr b, arr c) {
    if (t == 1) {
        *c = ksm(*b, mod - 2, *a);
        return;
    }
    int i;
    prep(t);
    t = n;
    Inv(t >> 1, b, pd);
    prep(t);
    t = n;
    cl(c);
    memcpy(c, a, (t >> 1) * szf);
    NTT(c);
    NTT(pd);
    for (i = 0; i < t; i++) c[i] = 1ll * c[i] * pd[i] % mod;
    INTT(c);
    fill(c + (t >> 1), c + t, 0);
    NTT(c, pb);
    NTT(b, pc);
    for (i = 0; i < t; i++) pb[i] = 1ll * pb[i] * pc[i] % mod;
    INTT(pb);
    fill(pb, pb + (t >> 1), 0);
    for (i = t >> 1; i < t; i++) pb[i] = sub(pb[i], a[i]);
    NTT(pb);
    for (i = 0; i < t; i++) pb[i] = 1ll * (mod - pb[i]) * pd[i] % mod;
    INTT(pb);
    i = t >> 1;
    memcpy(c + i, pb + i, i * szf);
    cl(pb);
    cl(pc);
    cl(pd);
}
}  // namespace poly

namespace dc_poly {
using namespace poly;
arr t1, t2, t3, t4;
void solve(int l, int r, arr a, arr b, arr f, arr g) {
    if (l + 1 == r) {
        f[0] = a[l];
        g[0] = 1;
        g[1] = sub(0, b[l]);
        return;
    }
    int mid = l + r >> 1, L = r - l >> 1;
    solve(l, mid, a, b, f, g);
    solve(mid, r, a, b, f + L + 1, g + L + 1);
    memcpy(t1, f, L * sizeof(int));
    memcpy(t2, g, (L + 1) * sizeof(int));
    memcpy(t3, f + L + 1, L * sizeof(int));
    memcpy(t4, g + L + 1, (L + 1) * sizeof(int));
    prep(L <<= 1);
    NTT(t1);
    NTT(t2);
    NTT(t3);
    NTT(t4);
    for (int i = 0; i < L; i++) t1[i] = (1ll * t1[i] * t4[i] + 1ll * t2[i] * t3[i]) % mod;
    for (int i = 0; i < L; i++) t2[i] = 1ll * t2[i] * t4[i] % mod;
    INTT(t1);
    INTT(t2);
    memcpy(f, t1, L * sizeof(int));
    f[L] = 0;
    memcpy(g, t2, L * sizeof(int));
    g[L] = sub(g[0], 1);
    g[0] = 1;
    g[L + 1] = 0;
    cl(t1);
    cl(t2);
    cl(t3);
    cl(t4);
}
}  // namespace dc_poly

int n, m, k, L;
arr kp, a, b, c, f, g, ans;

void clear_all() {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(c, 0, sizeof(c));
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(ans, 0, sizeof(ans));
    memset(poly::pa, 0, sizeof(poly::pa));
    memset(poly::pb, 0, sizeof(poly::pb));
    memset(poly::pc, 0, sizeof(poly::pc));
    memset(poly::pd, 0, sizeof(poly::pd));
    memset(dc_poly::t1, 0, sizeof(dc_poly::t1));
    memset(dc_poly::t2, 0, sizeof(dc_poly::t2));
    memset(dc_poly::t3, 0, sizeof(dc_poly::t3));
    memset(dc_poly::t4, 0, sizeof(dc_poly::t4));
}

void prep() {
    int im = ksm(m, mod - 2);
    kp[0] = 1;
    for (int i = 1; i <= n; i++) kp[i] = 1ll * kp[i - 1] * im % mod;
    c[0] = 1ll * (m - 1) * im % mod;
    for (int i = 1; i < n; i++)
        c[i] = (c[i - 1] + (1ll * ifac[i] * (m - 1) + 1ll * ifac[i + 1] * i) % mod * kp[i + 1]) % mod;
    c[n - 1] = 1;
    for (int i = 1; i < n; i++)
        c[n - 1] = (c[n - 1] + 1ll * ifac[i] * kp[i]) % mod;
    int coe = ksm(m, 2 * (n - 1), fac[n - 1]);
    for (int i = 0; i < n; i++) c[i] = 1ll * c[i] * coe % mod;
}

void solve() {
    clear_all();
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    prep();
    poly_base::r_prep(L = n << 1);
    for (int i = n; i < L; i++) a[i] = a[L - 1 - i];
    for (int i = n; i; i--) c[i] = c[i - 1];
    c[0] = 0;
    b[0] = sub(n, 3);
    b[1] = 1;
    b[L - 1] = 1;
    poly_base::prep(L);
    poly_base::NTT(a);
    poly_base::NTT(b);
    poly_base::NTT(c);
    for (int i = 0; i < L; i++) a[i] = 1ll * a[i] * c[i] % mod;
    for (int i = 2, l = 1, j = 2; i < L; i += l <<= 1)
        for (int k = 0; k < l; k++) {
            b[j] = b[i + k];
            a[j++] = add(a[i + k], a[i + (l << 1) - k - 1]);
        }
    dc_poly::solve(0, n, a, b, f, g);
    g[n] = 0;
    poly::Inv2(n, f, g, ans);
    for (int i = 0, t = a[n]; i < k; i++) {
        ans[i] = add(ans[i], t);
        t = 1ll * t * b[n] % mod;
    }
    int iv = ksm(L, mod - 2);
    for (int i = 0; i < k; i++)
        printf("%lld\n", 1ll * ans[i] * iv % mod);
}

int main() {
    int T;
    scanf("%d", &T);
    pre_f();
    while (T--) {
        solve();
    }
    return 0;
}