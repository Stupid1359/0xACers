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

const int N = 1e5 + 10;
const int M = N * 20;
const int P = 998244353;
int n, m;
int idx[N][20];
int idy[N][20];
int tot, bound, par[M << 1], pos[M << 1];
int cnt, num[M << 1], blo[N];
vector<int> g[N];

int qpow(int a, int b) {int s = 1; for(; b; b >>= 1) {if(b & 1) s = 1ll * s * a % P; a = 1ll * a * a % P;} return s;}

int find(int x) {return x == par[x] ? x : par[x] = find(par[x]);}
void merge(int x, int y) {par[find(x)] = find(y);}

int all = 0;
int now[N];

void dfs(int p) {
    if(all == 20) return;

    if(p == cnt + 1) {
        all ++;
        rep(i, 1, n) putchar(now[blo[i]] + 'a');
        puts("");
        return;
    }

    rep(i, 0, 25) {
        now[p] = i;
        dfs(p + 1);
        if(all == 20) return;
    }
}

void solve() {
    rep(i, 1, tot) pos[i] = 0, num[i] = 0;
    rep(i, 1, n) g[i].clear();
    tot = all = cnt = 0;

    n = read(), m = read();

    rep(i, 1, n) for(int j = 0; i + (1 << j) - 1 <= n; j ++) pos[idx[i][j] = ++ tot] = i;
    bound = tot;
    rep(i, 1, n) for(int j = 0; i - (1 << j) + 1 >= 1; j ++) pos[idy[i][j] = ++ tot] = i;
    
    rep(i, 1, tot) par[i] = i;
    while(m --) {
        int l = read(), r = read();
        if(l == r) continue;
        int len = (r - l + 1) >> 1;

        int curx = l;
        int cury = r;
        per(i, 16, 0) if(len >> i & 1) {
            merge(idx[curx][i], idy[cury][i]);
            curx += (1 << i);
            cury -= (1 << i);
        }
    }

    per(o, 16, 1) {
        rep(i, 1, n - (1 << o) + 1) {
            int cur = idx[i][o];
            int nxt = find(cur);
            int j = pos[nxt];

            if(cur != nxt) {
                merge(idx[i][o - 1], (nxt <= bound) ? idx[j][o - 1] : idy[j][o - 1]);
                merge(idx[i + (1 << (o - 1))][o - 1], (nxt <= bound) ? idx[j + (1 << (o - 1))][o - 1] : idy[j - (1 << (o - 1))][o - 1]); 
            }
        }
        rep(i, (1 << o), n) {
            int cur = idy[i][o];
            int nxt = find(cur);
            int j = pos[nxt];

            if(cur != nxt) {
                merge(idy[i][o - 1], (nxt <= bound) ? idx[j][o - 1] : idy[j][o - 1]);
                merge(idy[i - (1 << (o - 1))][o - 1], (nxt <= bound) ? idx[j + (1 << (o - 1))][o - 1] : idy[j - (1 << (o - 1))][o - 1]);
            }
        }
    }

    rep(i, 1, n) merge(idx[i][0], idy[i][0]);

    rep(i, 1, n) {
        int x = find(idx[i][0]);
        if(!num[x]) num[x] = ++ cnt;
        g[num[x]].push_back(i);
        blo[i] = num[x];
    }

    printf("%d\n", qpow(26, cnt));
    dfs(1);
}

int main() {
    int t = read(); while(t --) solve(); return 0;
}