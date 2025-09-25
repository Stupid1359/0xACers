#include <bits/stdc++.h>
#define ll long long
#define ssz(x) ((int)x.size())
using namespace std;
const int N = 3e5 + 5;
int n, q, id[N], fa[N][19], dep[N], F[N];
ll a[N], b[N], sumb[N], val[N][19];
vector<int> g[N];
int cmp(int x, int y) {
    return a[x] < a[y];
}
int find(int x) {
    return F[x] == x ? x : F[x] = find(F[x]);
}
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        id[i] = i;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    sort(id + 1, id + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        int u = id[i];
        F[u] = u;
        sumb[u] = b[u];
        for (int v : g[u]) {
            if (!F[v]) continue;
            int fv = find(v);
            fa[fv][0] = u;
            F[fv] = u;
            sumb[u] += sumb[fv];
            val[fv][0] = a[u] - sumb[fv];
        }
    }
    for (int i = n; i >= 1; i--)
        dep[id[i]] = dep[fa[id[i]][0]] + 1;
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i <= n; i++) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
            val[i][j] = max(val[i][j - 1], val[fa[i][j - 1]][j - 1]);
        }
    while (q--) {
        int x;
        ll y;
        cin >> x >> y;
        if (y < a[x]) {
            cout << y << "\n";
            continue;
        }
        for (int i = 17; i >= 0; i--)
            if (fa[x][i] && val[x][i] <= y)
                x = fa[x][i];
        cout << sumb[x] + y << "\n";
    }
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        memset(fa[i], 0, sizeof(fa[i]));
        memset(val[i], 0, sizeof(val[i]));
        a[i] = b[i] = sumb[i] = dep[i] = F[i] = 0;
    }
    memset(id, 0, sizeof(int) * (n + 1));
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}