#include<bits/stdc++.h>
typedef long long LL;
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

const int N = 2e5 + 10;
int n, q, a[N];

struct Tree{
	int len; LL f[4][4];
	void Clear(){
		for(int i = 0; i < 4; i ++)
			for(int j = 0; j < 4; j ++) f[i][j] = 0;		 
		len = 0;
	} Tree(){}
	Tree(int x){
		Clear();
		len = 1; f[1][1] = x;
	}
	Tree(Tree a, Tree b){
		Clear();
		len = a.len + b.len;
		for(int i = 0; i <= min(3, a.len); i ++)
			for(int j = 0; j <= min(3, b.len); j ++){
				if(i == a.len && j == b.len){
					if(i + j < 4)
						f[i + j][i + j] = a.f[i][i] + b.f[j][j];
					continue;
				}
				if(i == a.len){
					for(int k = 0; k <= min(3 - i, b.len); k ++)
						f[i + k][j] = max(f[i + k][j], a.f[i][i] + b.f[k][j]);
					continue;
				}
				if(j == b.len){
					for(int k = 0; k <= min(3 - j, a.len); k ++)
						f[i][j + k] = max(f[i][j + k], a.f[i][k] + b.f[j][j]);
					continue;
				}
				LL sum = 0;
				for(int k = 3; k >= 0; k --){
					sum = max(sum, b.f[3 - k][j]);
					f[i][j] = max(f[i][j], sum + a.f[i][k]);
				}
			}
	}
} t[N << 2];

void Build(int p, int l, int r){
	if(l == r){t[p] = Tree(a[l]); return;}
	int mid = (l + r) >> 1;
	Build(p << 1, l, mid);
	Build(p << 1 | 1, mid + 1, r);
	t[p] = Tree(t[p << 1], t[p << 1 | 1]);
}

void Modify(int p, int l, int r, int k, int v){
	if(l == r){t[p].f[1][1] = v; return;}
	int mid = (l + r) >> 1;
	if(k <= mid) Modify(p << 1, l, mid, k, v);
	else Modify(p << 1 | 1, mid + 1, r, k, v);
	t[p] = Tree(t[p << 1], t[p << 1 | 1]);
}

void Query(){
	LL ans = 0;
	for(int i = 0; i <= 3; i ++)
		for(int j = 0; j <= 3 - i; j ++)
			ans = max(ans, t[1].f[i][j]);
	printf("%lld\n", ans);
}

void solve() {
    n = read(), q = read();
	for(int i = 1; i <= n; i ++) a[i] = read();
	Build(1, 1, n);
	Query();
	for(int i = 1; i <= q; i ++){
		int u = read(), v = read();
		Modify(1, 1, n, u, v);
		Query();
	}
}

int main(){
    // freopen("a.in", "r", stdin);
    // freopen("a.out", "w", stdout);
	int t = read(); while(t --) solve(); return 0;
}