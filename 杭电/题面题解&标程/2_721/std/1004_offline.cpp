#include <bits/stdc++.h>

using s64 = long long;

template <class T>
inline void chmin(T &x, const T &y) {
    if (x > y) {
        x = y;
    }
}
template <class T>
inline void chmax(T &x, const T &y) {
    if (x < y) {
        x = y;
    }
}

/* ----- ----- ----- 正文 ----- ----- ----- */

const int N = 100100, M = 100100;
const int NewN = N * 2 + M;

const int mod = 1e9 + 7;

int n, m;
std::string str;

struct Graph {
    std::vector< std::vector<int> > table;

    void init(int _n) {
        table.assign(_n + 1, {});
    }

    void add_edge(int u, int v) {
        table[u].push_back(v);
    }
} G;

int ptr;
int minl[NewN], maxl[NewN];

namespace SAM {
    const int SIZE = N * 2;

    int NodeCount, Last;
    struct node {
        int trans[26];
        int link, maxl;
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

    std::map<int, int> buc[SIZE];

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
            buc[i].clear();
        }
        for (int i = 2; i <= NodeCount; i ++) {
            son[t[i].link].push_back(i);
        }

        for (int i = 1; i <= NodeCount; i ++) {
            buc[i][t[i].maxl] = 1;
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

    void dfs(int u, int fu) {
        for (auto &[L, p] : buc[u]) {
            p = ++ ptr;
            minl[p] = maxl[fu] + 1, maxl[p] = L;

            G.add_edge(fu, p);
            fu = p;
        }

        for (int v : son[u]) {
            dfs(v, fu);
        }
    }

    void build_newtree() {
        G.init(2 * n + m);

        ptr = 0;
        dfs(1, 0);
    }
}

std::pair<int, int> range[M];

int match[M];

int dep[NewN], sze[NewN], Fa[NewN], son[NewN];

void dfs1(int u, int fu) {
    dep[u] = dep[fu] + 1;
    sze[u] = 1;

    Fa[u] = fu;
    son[u] = 0;

    for (int v : G.table[u]) {
        dfs1(v, u);

        sze[u] += sze[v];
        if (sze[v] > sze[son[u]]) {
            son[u] = v;
        }
    }
}

int dfsClock, dfn[NewN], idx[NewN];
int Top[NewN];

void dfs2(int u, int P) {
    dfsClock ++;
    dfn[u] = dfsClock, idx[dfsClock] = u;

    Top[u] = P;

    if (son[u]) dfs2(son[u], P);
    for (int v : G.table[u]) {
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
        void mk_add(int k, int b) {
            int L = minl[idx[l]], R = maxl[idx[r]];
            s1 = (s1 + 1ll * k * f1(L, R) + 1ll * b * (R - L + 1)) % mod;
            s2 = (s2 + 1ll * k * f2(L, R) + 1ll * b * f1(L, R)) % mod;
            addk = (addk + k) % mod, addb = (addb + b) % mod;
        }
    } t[NewN * 4];

    void upd(int p) {
        t[p].s1 = (t[p * 2].s1 + t[p * 2 + 1].s1) % mod;
        t[p].s2 = (t[p * 2].s2 + t[p * 2 + 1].s2) % mod;
    }

    void spread(int p) {
        if (!t[p].addk && !t[p].addb) return;
        t[p * 2].mk_add(t[p].addk, t[p].addb), t[p * 2 + 1].mk_add(t[p].addk, t[p].addb);
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
            t[p].mk_add(k, b);
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

int ans;

void solve(int p) {
    int x, s1 = 0, s2 = 0;

    x = p;
    while (x) {
        s1 = (s1 + SGT::ask1(1, dfn[Top[x]], dfn[x])) % mod;
        s2 = (s2 + SGT::ask2(1, dfn[Top[x]], dfn[x])) % mod;
        x = Fa[Top[x]];
    }

    ans = (ans + 1ll * (maxl[p] + 1) * s1) % mod;
    ans = (ans - s2) % mod;

    x = p;
    while (x) {
        SGT::addRange(1, dfn[Top[x]], dfn[x], -1, maxl[p] + 1);
        x = Fa[Top[x]];
    }
}

void work() {   
    std::cin >> n >> m;
    std::cin >> str, str = " " + str;

    SAM::init();
    for (int i = n; i >= 1; i --) {
        SAM::extend(str[i] - 'a', i);
    }

    SAM::build_tree();

    for (int i = 1; i <= m; i ++) {
        int l, r;
        std::cin >> l >> r;

        range[i] = {l, r};

        int p = SAM::find(l, r);

        SAM::buc[p][r - l + 1] = 1;
        match[i] = p;
    }

    SAM::build_newtree();

    dfsClock = 0;
    dfs1(1, 0);
    dfs2(1, 1);

    SGT::build(1, 1, dfsClock);

    ans = 0;
    for (int i = 1; i <= m; i ++) {
        auto [l, r] = range[i];

        solve(SAM::buc[match[i]][r - l + 1]);

        ans = (ans + g(r - l + 1)) % mod;

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