#include<bits/stdc++.h>
typedef long long LL;
typedef unsigned long long ULL;
#define rep(i, a, b) for(int i = (a); i <= (b); i ++)
#define per(i, a, b) for(int i = (a); i >= (b); i --)
using namespace std;

inline int read() {
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? -1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f; 
}

const int N = 55;
const int M = 5e4 + 10;
const int Q = 5e5 + 10;
const LL inf = 1e18;
int n, m, q;
struct edge {int u, v, w, d;} e[M];
struct query {int l, r;} c[Q];
LL ans[Q];

bool cmp(edge a, edge b) {return a.w < b.w;}
bool cmp2(int a, int b) {return c[a].r < c[b].r;}

LL f[N][N], F[N], g[M][N];
vector<int> h[M], p[M];

void clear() {
	rep(i, 1, m) h[i].clear();
}

void solve(int L, int R) {
	bool flag = false;
	rep(i, L, R) flag |= !(h[i].empty());
	if(!flag) return;
	
	if(L > R) return;
	if(L == R) {
		for(auto o : h[L])
			if(c[o].r >= R) ans[o] = e[L].d;
		return;
	}
	
	int mid = (L + R) >> 1;
	rep(i, 1, n) {
		rep(j, 1, n) f[i][j] = -inf;
		f[i][i] = F[i] = 0;
	}
	rep(i, mid + 1, R) p[i].clear();
	
	per(i, mid, L) {
		int u = e[i].u, v = e[i].v;
		rep(x, 1, n) f[u][x] = max(f[u][x], e[i].d + f[v][x]), F[x] = max(F[x], f[u][x]);
		rep(x, 1, n) g[i][x] = F[x];
		while(!h[i].empty() && c[h[i].back()].r > mid) {
			p[c[h[i].back()].r].push_back(h[i].back());
			h[i].pop_back();
		}
	}
	
	rep(i, 1, n) {
		rep(j, 1, n) f[i][j] = -inf;
		f[i][i] = F[i] = 0;
	}
	rep(i, mid + 1, R) {
		int u = e[i].u, v = e[i].v;
		rep(x, 1, n) f[x][v] = max(f[x][v], e[i].d + f[x][u]), F[x] = max(F[x], f[x][v]);
		for(auto o : p[i]) {
			int cL = c[o].l;
			rep(x, 1, n) ans[o] = max(ans[o], g[cL][x] + F[x]);
		}
	}
	
	solve(L, mid);
	solve(mid + 1, R);
}

int W[M];

void solve() {
	clear();
	
	n = read(), m = read(), q = read();
	rep(i, 1, m)
		e[i].u = read(), e[i].v = read(), 
		e[i].w = read(), e[i].d = read();
	
	sort(e + 1, e + m + 1, cmp);
	
	rep(i, 1, m) W[i] = e[i].w;
	
	rep(i, 1, q) {
		c[i].l = read(), c[i].l = lower_bound(W + 1, W + m + 1, c[i].l) - W;
		c[i].r = read(), c[i].r = upper_bound(W + 1, W + m + 1, c[i].r) - W - 1;
		if(c[i].l <= m) h[c[i].l].push_back(i);
		ans[i] = 0;
	}
	
	rep(i, 1, m) sort(h[i].begin(), h[i].end(), cmp2);
	
	solve(1, m);
	
	rep(i, 1, q) printf("%lld\n", ans[i]);
}

int main() {
	int t = read(); while(t --) solve(); return 0;
}