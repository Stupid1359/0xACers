#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
static const int maxn = (int)1e5 + 9, maxm = 21, maxh = 41;

int n, m, dif, lim[maxm], que[maxh][maxn], qL[maxh], qR[maxh];
pair<int, int> a[maxn];
LL f[2][maxh][maxn];

void solve() {
    int n, m;
    scanf("%d%d%d", &m, &n, &dif);
    for(int i = 1; i <= m; ++i)
        scanf("%d", lim + i);
    sort(lim + 1, lim + m + 1);
    for(int i = 1; i <= n; ++i) {
        auto &[x, t] = a[i];
        scanf("%d%d", &x, &t);
        t = 2 - t;
    }
    sort(a + 1, a + n + 1);
    for( ; n > 0 && a[n].first > lim[m]; --n);
    // 考虑滚动选 2m 个人
    for(int i = 0; i <= m + m; ++i) {
        memset(f[0][i], -1, (n + 1) * sizeof(LL));
        memset(f[1][i], -1, (n + 1) * sizeof(LL));
    }
    f[1][0][0] = 0;
    for(int t = 1, iLim = 0, jLim = 2; t <= m; ++t, jLim += 2) {
        for( ; iLim < n && a[iLim + 1].first <= lim[t]; ++iLim);
        for(int j = 0; j <= jLim; ++j) {
            for(int i = 1; i <= iLim; ++i) {
                f[1][j][i] = max(f[1][j][i], f[1][j][i - 1]);
                if(!a[i].second) {
                    f[0][j][i] = f[1][j][i - 1];
                } else {
                    f[0][j][i] = j ? f[1][j - 1][i - 1] : -1;
                }
                if(f[0][j][i] == -1)
                    continue;
                f[0][j][i] += a[i].first;
                // printf("fir %d %d %d: %lld\n", t, j, i, f[0][j][i]);
            }
        }
        f[1][0][0] = -1;
        for(int j = 0; j <= jLim; ++j)
            qL[j] = qR[j] = 0;
        for(int i = 1; i <= iLim; ++i) {
            for(int j = 0; j <= jLim; ++j) {
                for( ; qL[j] < qR[j] && a[que[j][qL[j]]].first < a[i].first - dif; ++qL[j]);
                if(!a[i].second) {
                    f[1][j][i] = qL[j] < qR[j] ? f[0][j][que[j][qL[j]]] : -1;
                } else {
                    f[1][j][i] =j && qL[j - 1] < qR[j - 1] ? f[0][j - 1][que[j - 1][qL[j - 1]]] : -1;
                }
                if(f[1][j][i] == -1)
                    continue;
                f[1][j][i] += a[i].first;
                // printf("sec %d %d %d: %lld\n", t, j, i, f[1][j][i]);
            }
            for(int j = 0; j <= jLim; ++j) {
                if(f[0][j][i] == -1)
                    continue;
                for( ; qL[j] < qR[j] && f[0][j][que[j][qR[j] - 1]] <= f[0][j][i]; --qR[j]);
                que[j][qR[j]++] = i;
            }
        }
    }
    for(int i = 0; i <= m + m; ++i) {
        LL ans = -1;
        for(int j = 1; j <= n; ++j)
            ans = max(ans, f[1][i][j]);
        printf("%lld%c", ans, " \n"[i == m + m]);
    }
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: ", Case);
        solve();
    }
    return 0;
}
