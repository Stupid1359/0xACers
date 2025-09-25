#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
const int maxn = (int)1e5 + 9;

int n, q, a[maxn], c[2][maxn], *bits = c[0];
int blk, stp, pos[maxn], ord[maxn];
int m, sq, f[maxn], pL[maxn], pR[maxn], qL, qR;

struct Query {
    int typ, L, R, k;
    void read() {
        scanf("%d%d%d%d", &typ, &L, &R, &k);
    }
} que[maxn];

inline void bitsUpd(int x, int v) {
    for( ; x <= n; x += x & -x)
        bits[x] += v;
}

inline int bitsQry(int x) {
    int res = 0;
    for( ; x > 0; x -= x & -x)
        res += bits[x];
    return res;
}

inline void blkUpd(int pL, int pR, int d) {
    if(pL < qL || pR > qR)
        return;
    int &v = f[pR];
    c[0][v] += d;
    c[1][pos[v]] += d;
    // printf("upd %d (%d, %d): %d\n", v, pL, pR, d);
}

void solve() {
    scanf("%d%d", &n, &q);
    memset(bits + 1, 0, n * sizeof(int));
    memset(pos + 1, 0, n * sizeof(int));
    m = 0;
    for(int i = 1, j; i <= n; ++i) {
        scanf("%d", a + i);
        pL[i] = 0;
        pR[i] = n + 1;
        bitsUpd(i, 1);
        if((j = pos[a[i]]) > 0) {
            pL[i] = j;
            pR[j] = i;
            f[i] = bitsQry(i - 1) - bitsQry(j - 1);
            bitsUpd(j, -1);
            m = max(m, f[i]);
            // printf("[%d, %d]: %d\n", j, i, f[i]);
        }
        pos[a[i]] = i;
    }
    for(int i = 1; i <= q; ++i) {
        que[i].read();
        ord[i] = i;
    }
    if(!m) {
        for(int i = 1; i <= q; ++i)
            puts(que[i].typ == 1 ? "0" : "-1");
        return;
    }

    // event - O(n sqrt(q))
    blk = min(max(1, (int)round(sqrtl(q))), n);
    stp = (n - 1) / blk + 1;
    for(int i = 1; i <= n; ++i)
        pos[i] = i <= stp ? 1 : pos[i - stp] + 1;
    // printf("q %d blk %d stp %d\n", q, blk, stp);
    sort(ord + 1, ord + q + 1, [&](int const &u, int const &v) {
        if(pos[que[u].L] != pos[que[v].L])
            return pos[que[u].L] < pos[que[v].L];
        return pos[que[u].L] & 1 ? (que[u].R < que[v].R) : (que[u].R > que[v].R);
    });
    // printf("ord:");
    // for(int i = 1; i <= q; ++i)
    //     printf(" %d", ord[i]);
    // puts("");

    // domain - O(event + q sqrt(m))
    stp = (int)round(sqrtl(m));
    // assert(stp > 0);
    blk = (m - 1) / stp + 1;
    // printf("m %d stp %d blk %d\n", m, stp, blk);
    for(int i = 1; i <= m; ++i)
        pos[i] = i <= stp ? 1 : pos[i - stp] + 1;
    // assert(pos[m] == blk);

    qL = 1;
    qR = 0;
    memset(c[0] + 1, 0, m * sizeof(int));
    memset(c[1] + 1, 0, blk * sizeof(int));
    for(int i = 1; i <= q; ++i) {
        Query &cur = que[ord[i]];
        // move [qL, qR] to [cur.L, cur.R]
        for( ; qL > cur.L; --qL, blkUpd(qL, pR[qL], 1));
        for( ; qR < cur.R; ++qR, blkUpd(pL[qR], qR, 1));
        for( ; qR > cur.R; blkUpd(pL[qR], qR, -1), --qR);
        for( ; qL < cur.L; blkUpd(qL, pR[qL], -1), ++qL);
        // printf("processing %d [%d, %d] %d\n", cur.typ, cur.L, cur.R, cur.k);
        // process
        int res = 0;
        if(cur.typ == 1) {
            cur.k = min(cur.k, m);
            for(int i = 1; i < pos[cur.k]; ++i)
                res += c[1][i];
            for(int i = (pos[cur.k] - 1) * stp + 1; i <= cur.k; ++i)
                res += c[0][i];
            cur.k = res;
            continue;
        }
        for(res = 1; res <= blk; ++res) {
            if(cur.k <= c[1][res])
                break;
            cur.k -= c[1][res];
        }
        // printf("res %d cur.k %d\n", res, cur.k);
        if(res > blk) {
            cur.k = -1;
            continue;
        }
        // assert(cur.k <= c[1][res]);
        for(res = (res - 1) * stp + 1; ; ++res) {
            if(cur.k <= c[0][res])
                break;
            cur.k -= c[0][res];
        }
        cur.k = res;
    }
    for(int i = 1; i <= q; ++i)
        printf("%d\n", que[i].k);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case)
        solve();
    return 0;
}
