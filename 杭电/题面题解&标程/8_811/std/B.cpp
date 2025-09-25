#include<bits/stdc++.h>
typedef long long LL;
typedef unsigned long long ULL;
#define rep(i, a, b) for(int i = (a); i <= (b); i ++)
#define per(i, a, b) for(int i = (a); i >= (b); i --)
using namespace std;

#define mp make_pair
#define fi first
#define se second
typedef pair<int, int> PII;

inline int read() {
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? -1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f; 
}

const int N = 4e3 + 10;
const int inf = 1e9;
int n, m, k;
vector<PII> g[N];

int dis[N][2], pre[N], pos[N];
bool vis[N][2];
int fpo[N], fid[N];

void clear() {
    rep(i, 1, n) g[i].clear(), fid[i] = fpo[i] = 0;
}

void dij(int c, bool flag) {
    rep(i, 1, n)
        dis[i][0] = dis[i][1] = inf, 
        vis[i][0] = vis[i][1] = false, pre[i] = pos[i] = 0;
    dis[1][!flag] = 0;
    priority_queue<pair<int, PII>> q;
    q.push(mp(0, mp(1, !flag)));

    while(!q.empty()) {
        auto cur = q.top(); q.pop();
        int u = cur.se.fi;
        int o = cur.se.se;

        if(vis[u][o]) continue; else vis[u][o] = true;
        
        int len = g[u].size();
        rep(i, 0, len - 1) {
            int v = g[u][i].fi;
            int w = max(0, g[u][i].se - c);
            if(flag) {
                if(dis[v][0] > dis[u][0] + w)
                    dis[v][0] = dis[u][0] + w,
                    q.push(mp(-dis[v][0], mp(v, 0))), 
                    pre[v] = i, 
                    pos[v] = u;
            } else {
                int x = o & (fpo[v] == u && fid[v] == i);
                if(dis[v][x] > dis[u][o] + w)
                    dis[v][x] = dis[u][o] + w, 
                    q.push(mp(-dis[v][x], mp(v, x)));
            }
        }
    }
}

void work(bool flag) {
    int now = inf;
    
    rep(c, 0, 1000) {
        dij(c, flag);
        dis[n][0] += c * k;
        if(now > dis[n][0]) {
            now = dis[n][0];
            if(flag) {
                rep(i, 1, n) fid[i] = fpo[i] = 0;
                for(int o = n; o && (o != 1); o = pos[o]) fpo[o] = pos[o], fid[o] = pre[o];
            }
        }
    }

    if(!flag) printf("%d\n", now == inf ? -1 : now);
}

void solve() {
    clear();
    n = read(), m = read(), k = read();
    rep(i, 1, m) {
        int u = read(), v = read(), w = read();
        g[u].push_back(mp(v, w));
    }
    rep(i, 1, k) n ++, g[n - 1].push_back(mp(n, 0));

    work(1);
    work(0);
}

int main() {
	int t = read(); while(t --) solve(); return 0;
}