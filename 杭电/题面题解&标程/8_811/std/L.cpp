#include<bits/stdc++.h>
typedef long long LL;
#define rep(i, a, b) for(int i = (a); i <= (b); i ++)
#define per(i, a, b) for(int i = (a); i >= (b); i --)
#define Ede(i, u) for(int i = head[u]; i; i = e[i].nxt)
using namespace std;

int read() {
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? - 1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f;
}

const int N = 3010;
const int P = 998244353; 
int n, a[N], f[N][N], g[N][N];

int plu(int x, int y) {return x + y >= P ? x + y - P : x + y;}

void solve() {
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));

	n = read();
	rep(i, 1, n) a[i] = read();
	rep(i, 1, n) g[0][i] = 1;
	rep(i, 1, n) {
		f[i][i] = g[i - 1][i];
		int minn = a[i];
		per(j, i - 1, 1) if(a[j] < minn) f[i][j] = g[i - 1][j], minn = a[j];
		minn = a[i];
		rep(j, i + 1, n) if(a[j] < minn) f[i][j] = g[i - 1][j], minn = a[j];
		rep(j, 1, n) g[i][j] = plu(g[i][j - 1], f[i][j]);
	}
	printf("%d\n", g[n][n]);
}

int main() {
	int t = read(); while(t --) solve(); return 0;
}