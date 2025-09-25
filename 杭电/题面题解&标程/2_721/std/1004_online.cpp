#include <bits/stdc++.h>

using s64 = long long;

/* 取 min */
template <class T>
inline void chmin(T &x, const T &y) {
    if (x > y) {
        x = y;
    }
}
/* 取 max */
template <class T>
inline void chmax(T &x, const T &y) {
    if (x < y) {
        x = y;
    }
}

/* ----- ----- ----- 正文 ----- ----- ----- */

const int N = 100100;
const int SIZE = N * 2;

const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;

int n, m;
std::string str;

namespace SAM {
    int NodeCount, Last;
    struct node {
        int trans[26];
        int link, minl, maxl;
    } t[SIZE];

    std::vector<int> son[SIZE];
    int anc[18][SIZE];

    int create() {
        int p = ++ NodeCount;
        for (int c = 0; c < 26; c ++) {
            t[p].trans[c] = 0;
        }
        t[p].link = t[p].maxl = 0;
        return p;
    }

    void init() {
        NodeCount = 0, Last = create();
    }

    int location[N];

    void extend(int c, int i) {
        int p = Last,
            np = Last = create();
        
        t[np].maxl = t[p].maxl + 1;

        for (; p && t[p].trans[c] == 0; p = t[p].link) {
            t[p].trans[c] = np;
        }

        if (!p) {
            t[np].link = 1;
        } else {
            int q = t[p].trans[c];

            if (t[q].maxl == t[p].maxl + 1) {
                t[np].link = q;
            } else {
                int nq = ++ NodeCount; t[nq] = t[q];
                t[nq].maxl = t[p].maxl + 1;

                t[np].link = t[q].link = nq;

                for (; p && t[p].trans[c] == q; p = t[p].link) {
                    t[p].trans[c] = nq;
                }
            }
        }

        location[i] = np;
    }

    void build_tree() {
        for (int i = 1; i <= NodeCount; i ++) {
            son[i].clear();
        }
        for (int i = 2; i <= NodeCount; i ++) {
            son[t[i].link].push_back(i);
        }

        for (int i = 1; i <= NodeCount; i ++) {
            t[i].minl = t[t[i].link].maxl + 1;
            anc[0][i] = t[i].link;
        }
        for (int j = 1; j <= 17; j ++) {
            for (int i = 1; i <= NodeCount; i ++) {
                anc[j][i] = anc[j - 1][anc[j - 1][i]];
            }
        }
    }

    /* 子串定位 */
    int find(int l, int r) {
        int p = location[l];
        for (int i = 17; i >= 0; i --) {
            if (t[anc[i][p]].maxl >= r - l + 1) {
                p = anc[i][p];
            }
        }
        return p;
    }
}

int dep[SIZE], sze[SIZE], Fa[SIZE], son[SIZE];

void dfs1(int u, int fu) {
    dep[u] = dep[fu] + 1;
    sze[u] = 1;

    Fa[u] = fu;
    son[u] = 0;

    for (int v : SAM::son[u]) {
        dfs1(v, u);

        sze[u] += sze[v];
        if (sze[v] > sze[son[u]]) {
            son[u] = v;
        }
    }
}

int dfsClock, dfn[SIZE], idx[SIZE];
int Top[SIZE];

void dfs2(int u, int P) {
    dfsClock ++;
    dfn[u] = dfsClock, idx[dfsClock] = u;

    Top[u] = P;

    if (son[u]) dfs2(son[u], P);
    for (int v : SAM::son[u]) {
        if (v == son[u]) continue;
        dfs2(v, v);
    }
}

int f1(int n) {
    return (1ll * n * (n + 1) / 2) % mod;
}
int f1(int l, int r) {
    return f1(r) - f1(l - 1);
}

int f2(int n) {
    return (1ll * n * (n + 1) * (2 * n + 1) / 6) % mod;
}
int f2(int l, int r) {
    return f2(r) - f2(l - 1);
}

int g(int n) {
    return (1ll * n * (n + 1) * (n - 1) / 6) % mod;
}

namespace SGT {
    struct node {
        int l, r;
        int s1, s2;
        int addk, addb;
        void mk_addkb(int k, int b) {
            int L = SAM::t[idx[l]].minl, R = SAM::t[idx[r]].maxl;
            s1 = (s1 + 1ll * k * f1(L, R) + 1ll * b * (R - L + 1)) % mod;
            s2 = (s2 + 1ll * k * f2(L, R) + 1ll * b * f1(L, R)) % mod;
            addk = (addk + k) % mod, addb = (addb + b) % mod;
        }
    } t[SIZE * 4];

    void upd(int p) {
        t[p].s1 = (t[p * 2].s1 + t[p * 2 + 1].s1) % mod;
        t[p].s2 = (t[p * 2].s2 + t[p * 2 + 1].s2) % mod;
    }

    void spread(int p) {
        if (!t[p].addk && !t[p].addb) return;
        t[p * 2].mk_addkb(t[p].addk, t[p].addb), t[p * 2 + 1].mk_addkb(t[p].addk, t[p].addb);
        t[p].addk = t[p].addb = 0;
    }

    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r, t[p].s1 = t[p].s2 = t[p].addk = t[p].addb = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(p * 2, l, mid), build(p * 2 + 1, mid + 1, r);
    }

    void addRange(int p, int s, int e, int k, int b) {
        if (s <= t[p].l && t[p].r <= e) {
            t[p].mk_addkb(k, b);
            return;
        }
        spread(p);
        int mid = (t[p].l + t[p].r) >> 1;
        if (s <= mid) {
            addRange(p * 2, s, e, k, b);
        }
        if (mid < e) {
            addRange(p * 2 + 1, s, e, k, b);
        }
        upd(p);
    }

    void addPos(int p, int x, int L, int R, int k, int b) {
        if (t[p].l == t[p].r) {
            t[p].s1 = (t[p].s1 + 1ll * k * f1(L, R) + 1ll * b * (R - L + 1)) % mod;
            t[p].s2 = (t[p].s2 + 1ll * k * f2(L, R) + 1ll * b * f1(L, R)) % mod;
            return;
        }
        spread(p);
        int mid = (t[p].l + t[p].r) >> 1;
        if (x <= mid) {
            addPos(p * 2, x, L, R, k, b);
        } else {
            addPos(p * 2 + 1, x, L, R, k, b);
        }
        upd(p);
    }

    int ask1(int p, int s, int e) {
        if (s <= t[p].l && t[p].r <= e) {
            return t[p].s1;
        }
        spread(p);
        int mid = (t[p].l + t[p].r) >> 1;
        if (s <= mid && mid < e) {
            return (ask1(p * 2, s, e) + ask1(p * 2 + 1, s, e)) % mod;
        }
        if (s <= mid) {
            return ask1(p * 2, s, e);
        } else {
            return ask1(p * 2 + 1, s, e);
        }
    }
    int ask2(int p, int s, int e) {
        if (s <= t[p].l && t[p].r <= e) {
            return t[p].s2;
        }
        spread(p);
        int mid = (t[p].l + t[p].r) >> 1;
        if (s <= mid && mid < e) {
            return (ask2(p * 2, s, e) + ask2(p * 2 + 1, s, e)) % mod;
        }
        if (s <= mid) {
            return ask2(p * 2, s, e);
        } else {
            return ask2(p * 2 + 1, s, e);
        }
    }
}

int root[SIZE];
namespace SGTdy {
    const int pond = 10001000;

    int NodeCount;
    struct node {
        int lc, rc;
        int cnt;
        int sum;
        int v1;
        int v2;
    } t[pond];

    int create() {
        int p = ++ NodeCount;
        t[p].lc = t[p].rc = t[p].cnt = t[p].sum = t[p].v1 = t[p].v2 = 0;
        return p;
    }

    void init() {
        NodeCount = 0;
        for (int i = 1; i <= dfsClock; i ++) {
            root[i] = 0;
        }
    }

    void insert(int &p, int l, int r, int x, int v1, int v2) {
        if (!p) p = create();
        t[p].cnt ++, t[p].sum = (t[p].sum + x) % mod;
        t[p].v1 = (t[p].v1 + v1) % mod, t[p].v2 = (t[p].v2 + v2) % mod;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (x <= mid) {
            insert(t[p].lc, l, mid, x, v1, v2);
        } else {
            insert(t[p].rc, mid + 1, r, x, v1, v2);
        }
    }

    int askcnt(int p, int l, int r, int s, int e) {
        if (s <= l && r <= e) {
            return t[p].cnt;
        }
        int mid = (l + r) >> 1;
        if (s <= mid && mid < e) {
            return askcnt(t[p].lc, l, mid, s, e) + askcnt(t[p].rc, mid + 1, r, s, e);
        }
        if (s <= mid) {
            return askcnt(t[p].lc, l, mid, s, e);
        } else {
            return askcnt(t[p].rc, mid + 1, r, s, e);
        }
    }
    int asksum(int p, int l, int r, int s, int e) {
        if (s <= l && r <= e) {
            return t[p].sum;
        }
        int mid = (l + r) >> 1;
        if (s <= mid && mid < e) {
            return (asksum(t[p].lc, l, mid, s, e) + asksum(t[p].rc, mid + 1, r, s, e)) % mod;
        }
        if (s <= mid) {
            return asksum(t[p].lc, l, mid, s, e);
        } else {
            return asksum(t[p].rc, mid + 1, r, s, e);
        }
    }
    int askv1(int p, int l, int r, int s, int e) {
        if (s <= l && r <= e) {
            return t[p].v1;
        }
        int mid = (l + r) >> 1;
        if (s <= mid && mid < e) {
            return (askv1(t[p].lc, l, mid, s, e) + askv1(t[p].rc, mid + 1, r, s, e)) % mod;
        }
        if (s <= mid) {
            return askv1(t[p].lc, l, mid, s, e);
        } else {
            return askv1(t[p].rc, mid + 1, r, s, e);
        }
    }
    int askv2(int p, int l, int r, int s, int e) {
        if (s <= l && r <= e) {
            return t[p].v2;
        }
        int mid = (l + r) >> 1;
        if (s <= mid && mid < e) {
            return (askv2(t[p].lc, l, mid, s, e) + askv2(t[p].rc, mid + 1, r, s, e)) % mod;
        }
        if (s <= mid) {
            return askv2(t[p].lc, l, mid, s, e);
        } else {
            return askv2(t[p].rc, mid + 1, r, s, e);
        }
    }
}

namespace BIT {
    int cnt[SIZE], sum[SIZE];

    void init() {
        for (int i = 1; i <= dfsClock; i ++) {
            cnt[i] = sum[i] = 0;
        }
    }

    void add(int x, int y) {
        for (; x <= dfsClock; x += x & -x) {
            cnt[x] ++;
            sum[x] = (sum[x] + y) % mod;
        }
    }

    int askcnt(int x) {
        int ans = 0;
        for (; x; x -= x & -x) {
            ans += cnt[x];
        }
        return ans;
    }
    int asksum(int x) {
        int ans = 0;
        for (; x; x -= x & -x) {
            ans = (ans + sum[x]) % mod;
        }
        return ans;
    }
}

int ans;

void solve(int l, int r) {
    int p = SAM::find(l, r);

    int L = SAM::t[p].minl - 1, R = SAM::t[p].maxl;
    int v = (r - l + 1) - L, v1 = 1ll * (-f2(v) + f1(v)) * inv2 % mod, v2 = f1(v);

    int x, s1, s2, cnt, sum, val1, val2;

    /*
        ----- ----- 计算 part ----- -----
    */

    /* 计算 p 祖先的整块贡献 and 补充 p 祖先的散块贡献 */

    x = Fa[p], s1 = s2 = 0;
    while (x) {
        s1 = (s1 + SGT::ask1(1, dfn[Top[x]], dfn[x])) % mod;
        s2 = (s2 + SGT::ask2(1, dfn[Top[x]], dfn[x])) % mod;
        x = Fa[Top[x]];
    }

    ans = (ans + 1ll * ((r - l + 1) + 1) * s1) % mod;
    ans = (ans - s2) % mod;

    /* 补充 p 节点内部散块的贡献 */

    val1 = SGTdy::askv1(root[p], 0, R - L, 0, v);
    val2 = SGTdy::askv2(root[p], 0, R - L, 0, v);
    ans = (ans + val1) % mod;
    ans = (ans + 1ll * v * val2 % mod) % mod; 
    if (v < R - L) {
        cnt = SGTdy::askcnt(root[p], 0, R - L, v + 1, R - L);
        sum = SGTdy::asksum(root[p], 0, R - L, v + 1, R - L);
        ans = (ans + 1ll * v1 * cnt) % mod;
        ans = (ans + 1ll * v2 * sum) % mod;
    }

    /* 补充 p 后代对 p 节点散块的贡献 */

    cnt = BIT::askcnt(dfn[p] + sze[p] - 1) - BIT::askcnt(dfn[p]);
    sum = (BIT::asksum(dfn[p] + sze[p] - 1) - BIT::asksum(dfn[p]) - 1ll * cnt * L) % mod;
    ans = (ans + 1ll * v1 * cnt) % mod;
    ans = (ans + 1ll * v2 * sum) % mod;

    /* 计算 S[l : r] 内部的贡献 */

    ans = (ans + g(r - l + 1)) % mod;

    /*
        ----- ----- 修改 part ----- -----
    */

    /* 修改 p 祖先的整块贡献 */

    x = Fa[p];
    while (x) {
        SGT::addRange(1, dfn[Top[x]], dfn[x], -1, (r - l + 1) + 1);
        x = Fa[Top[x]];
    }

    /* 补充 p 作为散块时的贡献 */

    SGT::addPos(1, dfn[p], SAM::t[p].minl, r - l + 1, -1, (r - l + 1) + 1);

    /* 补充 p 节点内部散块的贡献 */

    SGTdy::insert(root[p], 0, R - L, v, v1, v2);

    /* 补充 p 作为后代时的贡献 */

    BIT::add(dfn[p], r - l + 1);
}

void work() {
    std::cin >> n >> m;
    std::cin >> str, str = " " + str;

    SAM::init();
    for (int i = n; i >= 1; i --) {
        SAM::extend(str[i] - 'a', i);
    }

    SAM::build_tree();

    dfsClock = 0;
    dfs1(1, 0);
    dfs2(1, 1);

    SGT::build(1, 1, dfsClock);
    SGTdy::init();
    BIT::init();

    ans = 0;
    for (int i = 1; i <= m; i ++) {
        int l, r;
        std::cin >> l >> r;

        solve(l, r);

        ans = (ans + mod) % mod;
        std::cout << ans << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T;
    std::cin >> T;

    while (T --) {
        work();
    }
    
    return 0;
}

/**
 *  心中无女人
 *  比赛自然神
 *  模板第一页
 *  忘掉心上人
**/