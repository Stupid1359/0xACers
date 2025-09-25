#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
static const int maxn = 7, maxm = 16, maxd = 49, maxs = 1 << maxm | 1, maxv = (int)1e3, Mod = 1000000007;

int q, n, m, d, a[maxm | 1][(maxn + 1) | 1], tot, prb[maxd], inv[maxv + 1];
LL msk[maxm | 1], f[maxm + 1][maxv + 1];
unordered_map<LL, int> hs;
unordered_map<LL, int> low;
int ans[maxs];

LL cost;
void dfs(int dep, int msk0, LL msk1, int cnt, int sum) {
    // printf("dfs %d %d %lld %d %d\n", dep, msk0, msk1, cnt, sum);
    if(dep == m) {
        if(msk0) {
            auto it = hs.find(msk1);
            if(it == hs.end()) {
                int &res = ans[msk0] = 0;
                for(int i = 1; i <= sum; ++i)
                    if(f[cnt][i]) res = (res + (f[cnt][i] % Mod + Mod) * tot % Mod * inv[i]) % Mod;
                hs.insert({msk1, res});
                // printf("new %lld: %.10f\n", msk1, res);
                cost += sum;
                // ++cost;
            } else {
                ans[msk0] = it -> second;
            }
            auto jt = low.insert({msk1, msk0}).first;
            jt -> second = min(jt -> second, msk0);
        }
        return;
    }
    dfs(dep + 1, msk0, msk1, cnt, sum);
    msk0 |= a[dep][n];
    // printf("chk %lld %lld : %lld\n", msk1, msk[dep], msk1 & msk[dep]);
    if((msk1 & msk[dep]) == msk[dep]) {
        dfs(dep + 1, msk0, msk1, cnt, sum);
        return;
    }
    ++cnt;
    memcpy(f[cnt], f[cnt - 1], (sum + 1) * sizeof(LL));
    cost += sum;
    // ++cost;
    for(int i = 0, o; i < n; ++i) {
        o = a[dep][i];
        if(msk1 & (1LL << o))
            continue;
        // printf("add %d to msk1\n", o);
        msk1 |= 1LL << o;
        o = prb[o];
        memset(f[cnt] + sum + 1, 0, o * sizeof(LL));
        for(int j = sum; j >= 0; --j)
            if(f[cnt][j]) f[cnt][j + o] -= f[cnt][j];
        sum += o;
        cost += sum;
        // ++cost;
    }
    dfs(dep + 1, msk0, msk1, cnt, sum);
}

void solve() {
    scanf("%d%d", &n, &q);
    m = n + n + 2;
    d = n * n;
    tot = 0;
    for(int i = 0; i < d; ++i) {
        scanf("%d", prb + i);
        tot += prb[i];
    }
    // printf("tot: %d\n", tot);
    assert(tot <= maxv);
    for(int i = 0; i < m; ++i) {
        a[i][n] = -1;
        msk[i] = 0;
        if(i < 2) {
            for(int j = 0, u = i ? n - 1 : 0, v = i ? n - 1 : n + 1; j < n; ++j, u += v)
                msk[i] |= 1LL << u;
        } else if(i & 1) {
            for(int j = 0, u = ((i >> 1) - 1) * n; j < n; ++j, ++u)
                msk[i] |= 1LL << u;
        } else {
            for(int j = 0, u = (i >> 1) - 1; j < n; ++j, u += n)
                msk[i] |= 1LL << u;
        }
        // printf("msk %d: %lld\n", i, msk[i]);
    }
    for(int i = 0; i < m; ++i) {
        LL mask = 0;
        static int seq[maxn];
        for(int j = 0, x, y; j < n; ++j) {
            scanf("%d%d", &x, &y);
            seq[j] = (--x) * n + (--y);
            mask |= 1LL << seq[j];
        }
        for(int j = 0; j < m; ++j)
            if(msk[j] == mask) {
                assert(a[j][n] == -1);
                memcpy(a[j], seq, n * sizeof(int));
                a[j][n] = 1 << i;
                mask = -1;
                // printf("found %d: %lld %d\n", j, msk[j], 1 << i);
                break;
            }
        // if(mask != -1) {
        //     fprintf(stderr, "n %d m %d i %d msk %lld\n", n, m, i, mask);
        //     for(int j = 0; j < n; ++j)
        //         fprintf(stderr, "(%d %d)%c", seq[j] / n + 1, seq[j] % n + 1, " \n"[j == n - 1]);
        // }
        assert(mask == -1);
    }
    cost = 0;
    f[0][0] = -1;
    hs.clear();
    dfs(0, 0, 0LL, 0, 0);
    fprintf(stderr, "cost: %lld\n", cost);
    // for(auto &it: low)
    //     printf("%d %lld\n", it.second, it.first);
    for(int i = 0, x; i < q; ++i) {
        scanf("%d", &x);
        printf("%d\n", ans[x]);
    }
}

// void prepare() {
//     for(int n = 2; n <= 8; ++n) {
//         unordered_map<LL, vector<int> > f, g;
//         f[0LL].push_back({0});
//         for(int i = 0; i < n + n + 2; ++i) {
//             LL msk = 0;
//             if(i < n) {
//                 for(int j = 0, u = i * n; j < n; ++j, ++u)
//                     msk |= 1LL << u;
//             } else if(i < n + n) {
//                 for(int j = 0, u = i - n; j < n; ++j, u += n)
//                     msk |= 1LL << u;
//             } else {
//                 for(int j = 0, u = i > n + n ? n - 1 : 0, v = i > n + n ? n - 1 : n + 1; j < n; ++j, u += v)
//                     msk |= 1LL << u;
//             }
//             g = f;
//             for(auto &[k, vec]: f)
//                 for(int x: vec)
//                     g[k | msk].push_back(x | (1 << i));
//             f.swap(g);
//         }
//         LL cnt = 0;
//         for(auto &[k, vec]: f)
//             cnt += __builtin_popcountll(k);
//             // printf("%lld (%d): %d\n", k, __builtin_popcountll(k), (int)vec.size());
//         printf("n %d, state %d (%d), bits %lld, better %lld\n", n, f.size(), 1 << (n + n + 2), cnt, ((LL)n << (n + n + 2)));
//         fflush(stdout);
//     }
// }

int main() {
    inv[1] = 1;
    for(int i = 2; i<= maxv; ++i)
        inv[i] = 1LL * (Mod - Mod / i) * inv[Mod % i] % Mod;
    int T = 1;
    scanf("%d", &T);
    // prepare();
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: ", Case);
        solve();
    }
    return 0;
}
