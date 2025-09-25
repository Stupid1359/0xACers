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

const int N = 5e5 + 10;
int n, len, tot, L, R, blo[N];
LL s[N], v[N];

void solve() {
    rep(i, 1, max(len, tot)) s[i] = v[i] = blo[i] = 0;

    n = read();
    s[1] = 0;
    s[tot = len = 2] = read();

    blo[1] = 1;
    blo[2] = 2;

    L = 1, R = 2;

    while(n --) {
        int opt = read();
        if(opt == 1) {
            int w = read();
            tot ++, len ++;

            blo[tot] = len;
            v[tot] = 0;
            s[len] = s[len - 1] + w;
            R = len;
        } else if(opt == 2) {
            int x = read(), w = read();
            tot ++;
            blo[tot] = blo[x];
            v[tot] = v[x] + w;
            
            int par = blo[tot];

            assert(v[tot] <= s[par]);
            assert(v[tot] <= s[len] - s[par]);
            if(v[tot] == s[par]) L = max(L, par);
            if(v[tot] == s[len] - s[par]) R = min(R, par);
        } else {
            printf("%lld\n", s[R] - s[L]);
        }
    }
}

int main() {
    int t = read(); while(t --) solve(); return 0;
}