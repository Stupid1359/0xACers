#include<bits/stdc++.h>
typedef long long ll;
#define rep(i, a, b) for(int i = (a); i <= (b); i ++)
#define per(i, a, b) for(int i = (a); i >= (b); i --)
#define Ede(i, u) for(int i = head[u]; i; i = e[i].nxt)
using namespace std;
 
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? - 1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f;
}
 
const int N = 1e6 + 10;
const int inf = 1e9;
int n, m = 1000000, q, a[N], c[N];
struct node {int l, r, x, y;} cur, dat1[N << 2], dat2[N << 2];
int idx[N], rev[N];
 
node mer1(node o, int p) {
	if(o.l == -inf && o.x == -1) return dat1[p];
	if(o.x == -1) {
		o.x = dat1[p].x;
		o.l = max(o.l, dat1[p].l);
		o.r = min(o.r, dat1[p].r);
		return o;
	}
	else {
		if(dat2[p].x == -1) return o;
		o.l = max(o.l, max(dat2[p].l, min(o.x, dat2[p].x)));
		o.r = min(o.r, min(dat2[p].r, max(o.x, dat2[p].x)));
		o.x = dat2[p].y;
		return o;
	}
}
 
node mer2(node o, int p) {
	if(o.x == -1) return dat2[p];
	if(o.y == -1) {
		o.y = dat1[p].x;
		o.l = max(o.l, dat1[p].l);
		o.r = min(o.r, dat1[p].r);
		return o;
	}
	else {
		if(dat2[p].x == -1) return o;
		o.l = max(o.l, max(dat2[p].l, min(o.y, dat2[p].x)));
		o.r = min(o.r, min(dat2[p].r, max(o.y, dat2[p].x)));
		o.y = dat2[p].y;
		return o;
	}
}
 
void moi(int p, int l, int r, int k, int v) {
	if(l == r) return dat1[p] = dat2[p] = (node) {-inf, inf, v, -1}, void();
	int mid = (l + r) >> 1;
	if(k <= mid) moi(p << 1, l, mid, k, v); else moi(p << 1 | 1, mid + 1, r, k, v);
	dat1[p] = mer1(dat1[p << 1], p << 1 | 1);
	dat2[p] = mer2(dat2[p << 1], p << 1 | 1);
}
 
void que(int p, int l, int r) {
	if(l == r) {
		node now = mer1(cur, p);
		if(now.l < now.r) cur = now;
		return;
	}
	int mid = (l + r) >> 1;
	node now = mer1(cur, p << 1);
	if(now.l < now.r) cur = now, que(p << 1 | 1, mid + 1, r);
	else que(p << 1, l, mid);
}

bool cmp(int x, int y) {return c[x] < c[y];}

void solve() {
    n = read(), q = read();
    rep(i, 1, n) a[i] = m - read() + 1;
    rep(i, 1, n) c[i] = read(), idx[i] = i;
    sort(idx + 1, idx + n + 1, cmp);
    rep(i, 1, n) rev[idx[i]] = i;

    rep(i, 1, m << 2) dat1[i] = dat2[i] = (node) {-inf, inf, -1, -1};
	rep(i, 1, n) moi(1, 1, m, a[i], rev[i]);
 
	while(q --) {
        int opt = read();
        if(opt == 1) {
			int x = read(), y = m - read() + 1;
			moi(1, 1, m, a[x], -1);
			moi(1, 1, m, a[x] = y, rev[x]);
		}
		else {
			cur = (node) {-inf, inf, -1, -1}; que(1, 1, m);
			int ans = 0;
			if(cur.x < cur.l) ans = cur.l;
			else if(cur.x > cur.r) ans = cur.r;
			else ans = cur.x;
			printf("%d\n", idx[ans]);
		}
	}
}

int main() {
	int T = read(); while(T --) solve(); return 0;
}