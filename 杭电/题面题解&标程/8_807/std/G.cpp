#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e5 + 9, maxm = (int)2e5 + 9, maxl = 19, mod = (int)1e9 + 7;

int n, m, q, dsu[maxn], up[maxn];
int tot, que[maxm], ctr[maxm];
vector<array<int, 3> > e;

int tricks;

int dsuFind(int u) {
    return dsu[u] < 0 ? u : (dsu[u] = dsuFind(dsu[u]));
}

array<int, 3> lca(int u, int v) {
    assert(u != v);
    static int seq[2][maxl], &sz0 = seq[0][0], &sz1 = seq[1][0];
    sz0 = sz1 = 0;
    for(int x = u; x >= 0; seq[0][++sz0] = x, x = dsu[x]);
    for(int x = v; x >= 0; seq[1][++sz1] = x, x = dsu[x]);
    int x = seq[0][sz0], y = seq[1][sz1];
    if(x != y)
        return {x, y, -1};
    for( ; sz0 && sz1 && seq[0][sz0] == seq[1][sz1]; --sz0, --sz1);
    int z = max(sz0 ? up[seq[0][sz0]] : 0, sz1 ? up[seq[1][sz1]] : 0);
    return {x, y, z};
}

void solve() {
    scanf("%d%d%d", &n, &m, &q);
    int rem = n;
    memset(dsu + 1, -1, n * sizeof(int));
    e.resize(m);
    for(int i = 0; i < m; ++i) {
        auto &[u, v, w] = e[i];
        scanf("%d%d%d", &u, &v, &w);
        int x = dsuFind(u), y = dsuFind(v);
        if(x == y)
            continue;
        --rem;
        if(dsu[x] < dsu[y])
            swap(x, y);
        dsu[y] += dsu[x];
        dsu[x] = y;
    }
    if(rem > 2) {
        tricks |= 4;
        puts("0");
        return;
    }
    if(rem > 1) {
        tricks |= 8;
        int u, v;
        for(u = 1; u <= n && dsu[u] >= 0; ++u);
        for(v = u + 1; v <= n && dsu[v] >= 0; ++v);
        int ans = (LL)dsu[u] * dsu[v] % mod * q % mod;
        printf("%d\n", ans);
        return;
    }
    if(m == n * (n - 1LL) / 2) {
        tricks |= 16;
        // trick: (C(n, 2)-m)%mod == 0
        // e.g. 44723, 50996; 44724, 95719; 63248, 123114; 89445, 159262
        puts("0");
        return;
    }
    if((n * (n - 1LL) / 2 - m) % mod == 0)
        tricks |= 1;
    memset(dsu + 1, -1, n * sizeof(int));
    sort(e.begin(), e.end(), [&](auto const &u, auto const &v) {
        return u.at(2) < v.at(2);
    });
    tot = 0;
    if(m > 0 && e[0].at(2) > 1) {
        que[++tot] = 1;
        ctr[tot] = 0;
    }
    for(int i = 0; i < m; ) {
        que[++tot] = e[i].at(2);
        ctr[tot] = 0;
        for( ; i < m; ++i) {
            auto &[u, v, w] = e[i];
            if(w != que[tot])
                break;
            array<int, 3> res = lca(u, v);
            auto &[x, y, z] = res;
            if(z >= 0) {
                // trick: covered by previous connected edges
                // printf("#%d %d %d %d: fix %d\n", i, u, v, w, z);
                tricks |= 2;
                (++ctr[z]) >= mod && (ctr[z] -= mod);
                continue;
            }
            if(dsu[x] < dsu[y])
                swap(x, y);
            // printf("#%d %d %d %d: merge %d (%d) <- %d (%d) at %d (%d)\n", i, u, v, w, x, -dsu[x], y, -dsu[y], tot, que[tot]);
            (ctr[tot] = (ctr[tot] - (LL)dsu[x] * dsu[y] + 1) % mod) < 0 && (ctr[tot] += mod);
            dsu[y] += dsu[x];
            dsu[x] = y;
            up[x] = tot;
        }
    }
    int ans = 0;
    ctr[1] = (ctr[1] + n * (n - 1LL) / 2 - m) % mod;
    // printf("%d", ctr[1]);
    for(int i = 1; i < tot; ++i) {
        ans = (ans + (LL)(que[i + 1] - que[i]) * ctr[i]) % mod;
        // printf(" %d", ctr[i + 1]);
        (ctr[i + 1] += ctr[i]) >= mod && (ctr[i + 1] -= mod);
    }
    // puts("");
    printf("%d\n", ans);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: ", Case);
        solve();
    }
    {
        static const int maxp = 5;
        static char msk[7];
        for(int i = 0, tp = tricks; i < maxp; ++i, tp >>= 1)
            msk[i] = "01"[tp & 1];
        msk[maxp] = '\0';
        fprintf(stderr, "tricks: %s\n", msk);
    }
    return 0;
}
