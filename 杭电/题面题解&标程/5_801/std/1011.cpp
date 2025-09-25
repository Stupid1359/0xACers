#include <bits/stdc++.h>
using namespace std;
#define cs const
#define pb push_back
#define bg begin
#define pii pair<int, int>
#define fi first
#define se second
#define ll long long
cs int RLEN = 1 << 20 | 1;
inline char gc() {
    static char ibuf[RLEN], *ib, *ob;
    (ib == ob) && (ob = (ib = ibuf) + fread(ibuf, 1, RLEN, stdin));
    return (ib == ob) ? EOF : *ib++;
}
inline int read() {
    char ch = gc();
    int res = 0;
    bool f = 1;
    while (!isdigit(ch)) f ^= ch == '-', ch = gc();
    while (isdigit(ch)) res = (res + (res << 2) << 1) + (ch ^ 48), ch = gc();
    return f ? res : -res;
}
template <class tp>
inline void chemx(tp &a, tp b) { a < b ? a = b : 0; }
template <class tp>
inline void chemn(tp &a, tp b) { a > b ? a = b : 0; }
cs int N = 1000005;
int n, n1, n2, m1, m2, tim[N];
vector<pii> e1[N], e2[N];
struct pt {
    int x, y;
} ps1[N], ps2[N];
namespace Lct {
cs int M = 1000005;
int val[M], rev[M], s[M], c[M], mx[M], xs[M], tot, fa[M], son[M][2];
#define lc(u) son[u][0]
#define rc(u) son[u][1]
inline bool isrt(int u) {
    return !fa[u] || (rc(fa[u]) != u && lc(fa[u]) != u);
}
inline bool isrc(int u) {
    return rc(fa[u]) == u;
}
inline void pushup(int u) {
    s[u] = (u <= n) + xs[u];
    mx[u] = c[u];
    if (lc(u)) {
        s[u] += s[lc(u)];
        if (tim[mx[lc(u)]] > tim[mx[u]]) mx[u] = mx[lc(u)];
    }
    if (rc(u)) {
        s[u] += s[rc(u)];
        if (tim[mx[rc(u)]] > tim[mx[u]]) mx[u] = mx[rc(u)];
    }
}
inline void pushnow(int u) {
    swap(lc(u), rc(u)), rev[u] ^= 1;
}
inline void pushdown(int u) {
    if (!rev[u]) return;
    if (lc(u)) pushnow(lc(u));
    if (rc(u)) pushnow(rc(u));
    rev[u] = 0;
}
inline void rotate(int v) {
    int u = fa[v], z = fa[u];
    int t = isrc(v);
    if (!isrt(u)) son[z][isrc(u)] = v;
    fa[v] = z;
    son[u][t] = son[v][t ^ 1];
    fa[son[v][t ^ 1]] = u;
    fa[u] = v, son[v][t ^ 1] = u;
    pushup(u), pushup(v);
}
int stk[N], top;
inline void splay(int u) {
    stk[top = 1] = u;
    for (int v = u; !isrt(v); v = fa[v]) stk[++top] = fa[v];
    for (int i = top; i; i--) pushdown(stk[i]);
    while (!isrt(u)) {
        if (!isrt(fa[u]))
            isrc(u) == isrc(fa[u]) ? rotate(fa[u]) : rotate(u);
        rotate(u);
    }
    pushup(u);
}
inline void access(int u) {
    for (int v = 0; u; v = u, u = fa[u]) {
        splay(u);
        if (rc(u)) xs[u] += s[rc(u)];
        if (v) xs[u] -= s[v], fa[v] = u;
        rc(u) = v, pushup(u);
    }
}
inline int findrt(int u) {
    access(u), splay(u);
    while (pushdown(u), lc(u)) u = lc(u);
    splay(u);
    return u;
}
inline void makert(int u) {
    access(u), splay(u), pushnow(u);
}
inline void link(int u, int v) {
    if (findrt(u) == findrt(v)) return;
    access(u), splay(u), makert(v), fa[v] = u, xs[u] += s[v];
    pushup(u);
}
inline void cut(int u, int v) {
    makert(u), access(v), splay(v);
    fa[lc(v)] = 0, lc(v) = 0, pushup(u), pushup(v);
}
inline int querysize(int u) {
    access(u), splay(u);
    return s[u];
}
inline int querypos(int u, int v) {
    makert(u), access(v), splay(v);
    return mx[v];
}
}  // namespace Lct
using namespace Lct;
int a[N], b[N], cnt1, cnt2;
int pos1[N], pos2[N], pe1[N], pe2[N];
vector<int> p1[N], p2[N];
pii E1[N], E2[N];
ll sum[N];
struct edge {
    int op, v, u, w;
    friend inline bool operator<(cs edge &a, cs edge &b) {
        return a.w < b.w;
    }
} EE[N];
void clear() {
    for (int i = 0; i <= tot; i++) {
        val[i] = rev[i] = s[i] = c[i] = mx[i] = xs[i] = fa[i] = son[i][0] = son[i][1] = 0;
        pos1[i] = pos2[i] = pe1[i] = pe2[i] = sum[i] = 0;
        p1[i].clear(), p2[i].clear();
        e1[i].clear(), e2[i].clear();
    }
    cnt1 = cnt2 = tot = 0;
}
inline void cutedge(int id) {
    int u = E2[id].fi, v = E2[id].se;
    if (findrt(u) == findrt(pe2[id])) {
        cut(u, pe2[id]);
    }
    if (findrt(v) == findrt(pe2[id])) {
        cut(v, pe2[id]);
    }
}
inline void deletnode(int u) {
    for (int i = 0; i < e2[u].size(); i++) {
        int id = e2[u][i].se;
        cutedge(id);
    }
}
inline void insertnode(int u) {
    for (int i = 0; i < e1[u].size(); i++) {
        int v = e1[u][i].fi, id = e1[u][i].se;
        if (findrt(u) == findrt(v)) {
            int pos = querypos(u, v);
            cutedge(pos);
        }
        link(v, pe1[id]), link(u, pe1[id]);
    }
}
int ff[N];
int find(int x) {
    return ff[x] == x ? x : ff[x] = find(ff[x]);
}
int main() {
#ifdef Stargazer
    freopen("1.in", "r", stdin);
#endif
    int T = read();
    while (T--) {
        n = read(), n1 = read(), n2 = read();
        m1 = read(), m2 = read();
        for (int i = 1; i <= n; i++) val[++tot] = 1, pushup(tot);
        for (int i = 1; i <= n1; i++) pos1[i] = ++tot;
        for (int i = 1; i <= m1; i++) pe1[i] = ++tot;
        for (int i = 1; i <= n1; i++) {
            ps1[i].x = read(), ps1[i].y = read();
            a[i] = ps1[i].y;
        }
        sort(a + 1, a + n1 + 1);
        cnt1 = unique(a + 1, a + n1 + 1) - a - 1;
        for (int i = 1; i <= n1; i++) {
            ps1[i].y = lower_bound(a + 1, a + cnt1 + 1, ps1[i].y) - a;
            p1[ps1[i].y].pb(pos1[i]);
        }
        for (int i = 1; i <= n2; i++) {
            ps2[i].x = read(), ps2[i].y = -read();
            a[i] = ps2[i].y;
        }
        for (int i = 1; i <= n2; i++) pos2[i] = ++tot;
        for (int i = 1; i <= m2; i++) pe2[i] = ++tot;
        sort(a + 1, a + n2 + 1);
        cnt2 = unique(a + 1, a + n2 + 1) - a - 1;
        for (int i = 1; i <= n2; i++) {
            ps2[i].y = lower_bound(a + 1, a + cnt2 + 1, ps2[i].y) - a;
            p2[ps2[i].y].pb(pos2[i]);
        }
        for (int i = cnt1; i; i--) sum[i] = sum[i + 1] + (ll)p1[i].size();
        for (int i = 1; i <= m1; i++) {
            int op = read(), v = read(), u = read();
            if (op == 1)
                EE[i] = (edge){op, v, u, ps1[u].y};
            else
                EE[i] = (edge){op, v, u, max(ps1[u].y, ps1[v].y)};
        }
        sort(EE + 1, EE + m1 + 1);
        for (int i = 1; i <= n + n1; i++) ff[i] = i;
        for (int i = 1; i <= m1; i++) {
            int op = EE[i].op, v = EE[i].v, u = EE[i].u;
            int f1 = u, f2 = v;
            f1 += n;
            if (op == 2) f2 += n;
            f1 = find(f1), f2 = find(f2);
            if (f1 == f2) continue;
            ff[f1] = f2;
            if (op == 2) {
                if (ps1[u].y < ps1[v].y) swap(u, v);
                v = pos1[v];
            }
            u = pos1[u];
            e1[u].pb(pii(v, i));
            E1[i] = pii(u, v);
        }
        for (int i = 1; i <= m2; i++) {
            int op = read(), v = read(), u = read();
            if (op == 1)
                EE[i] = (edge){op, v, u, ps2[u].y};
            else
                EE[i] = (edge){op, v, u, max(ps2[u].y, ps2[v].y)};
        }
        sort(EE + 1, EE + m2 + 1);
        for (int i = 1; i <= n + n2; i++) ff[i] = i;
        for (int i = 1; i <= m2; i++) {
            int op = EE[i].op, v = EE[i].v, u = EE[i].u;
            int f1 = u, f2 = v;
            f1 += n;
            if (op == 2) f2 += n;
            f1 = find(f1), f2 = find(f2);
            if (f1 == f2) continue;
            ff[f1] = f2;

            if (op == 2 && ps2[u].y < ps2[v].y) swap(u, v);
            tim[i] = ps2[u].y;

            c[pe2[i]] = i;
            pushup(pe2[i]);
            u = pos2[u];
            if (op == 2) v = pos2[v];
            E2[i] = pii(u, v);
            if (op == 1) {
                link(u, pe2[i]), link(v, pe2[i]);
            } else {
                link(u, pe2[i]), link(v, pe2[i]);
            }
            e2[u].pb(pii(v, i));
        }
        ll res = 0;
        for (int i = cnt2, j = 1; i; i--) {
            for (int t = 0; t < p2[i].size(); t++) {
                int u = p2[i][t];
                deletnode(u);
            }
            while (querysize(1) < n && j <= cnt1) {
                for (int t = 0; t < p1[j].size(); t++) {
                    int u = p1[j][t];
                    insertnode(u);
                }
                j++;
            }
            res += 1ll * p2[i].size() * sum[j];
        }
        cout << res << '\n';
        clear();
    }
    return 0;
}
