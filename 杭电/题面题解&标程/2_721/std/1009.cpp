#include <bits/stdc++.h>

using s64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

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

int n, m;
int a[N], tag[N];

struct Graph {
    std::vector< std::vector<int> > table;

    void init(int _n) {
        table.assign(_n + 1, {});
    }

    void add_edge(int u, int v) {
        table[u].push_back(v);
    }
} G;

int dep[N], sze[N], Fa[N], son[N];

void dfs1(int u, int fu) {
    dep[u] = dep[fu] + 1;
    sze[u] = 1;

    Fa[u] = fu;
    son[u] = 0;

    for (int v : G.table[u]) {
        if (v == fu) continue;

        Fa[v] = u;
        dfs1(v, u);

        sze[u] += sze[v];
        if (sze[v] > sze[son[u]]) {
            son[u] = v;
        }
    }
}

int dfsClock, dfn[N], idx[N];
int Top[N];

void dfs2(int u, int P) {
    dfsClock ++;
    dfn[u] = dfsClock, idx[dfsClock] = u;

    Top[u] = P;

    if (son[u]) {
        dfs2(son[u], P);
    }
    for (int v : G.table[u]) {
        if (v == Fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

namespace SGT {
    struct node {
        int max;
    } t[N * 4];

    void upd(int p) {
        t[p].max = std::max(t[p * 2].max, t[p * 2 + 1].max);
    }

    void build(int p, int l, int r) {
        if (l == r) {
            t[p].max = a[idx[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(p * 2, l, mid), build(p * 2 + 1, mid + 1, r);
        upd(p);
    }

    void change(int p, int l, int r, int x, int y) {
        if (l == r) {
            t[p].max += y;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            change(p * 2, l, mid, x, y);
        } else {
            change(p * 2 + 1, mid + 1, r, x, y);
        }
        upd(p);
    }

    int ask(int p, int l, int r, int s, int e) {
        if (s <= l && r <= e) {
            return t[p].max;
        }
        int mid = (l + r) >> 1;
        if (s <= mid && mid < e) {
            return std::max(ask(p * 2, l, mid, s, e), ask(p * 2 + 1, mid + 1, r, s, e));
        }
        if (s <= mid) {
            return ask(p * 2, l, mid, s, e);
        } else {
            return ask(p * 2 + 1, mid + 1, r, s, e);
        }
    }
}

int path_ask(int x, int y) {
    int ans = 0;

    while (Top[x] ^ Top[y]) {
        if (dep[Top[x]] > dep[Top[y]]) std::swap(x, y);
        
        chmax(ans, SGT::ask(1, 1, n, dfn[Top[y]], dfn[y]));
        chmax(ans, a[Top[y]] + tag[Fa[Top[y]]]);

        y = Fa[Top[y]];
    }

    if (dep[x] > dep[y]) std::swap(x, y);

    chmax(ans, SGT::ask(1, 1, n, dfn[x], dfn[y]));
    if (x == Top[x]) chmax(ans, a[x] + tag[Fa[x]]);

    return ans;
}

void change(int x, int z) {
    if (Fa[x]) {
        SGT::change(1, 1, n, dfn[Fa[x]], z);
        a[Fa[x]] += z;
    }
    if (son[x]) {
        SGT::change(1, 1, n, dfn[son[x]], z);
    }
    tag[x] += z;
}

void work() {
    std::cin >> n >> m;

    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; i ++) {
        tag[i] = 0;
    }

    G.init(n);
    for (int i = 1; i < n; i ++) {
        int x, y;
        std::cin >> x >> y;

        G.add_edge(x, y), G.add_edge(y, x);
    }

    dfsClock = 0;
    dfs1(1, 0);
    dfs2(1, 1);

    SGT::build(1, 1, n);

    while (m --) {
        int opt, x, y;
        std::cin >> opt >> x >> y;

        if (opt == 1) {
            std::cout << path_ask(x, y) << '\n';
        } else {
            change(x, y);
        }
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