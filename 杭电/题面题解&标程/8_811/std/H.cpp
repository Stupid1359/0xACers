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

const int N = 1e5 + 10;
const int M = 35;
int n, m, k;
char s[N], t[M];

void solve() {
	n = read(), m = read();
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	k = m;
	
	reverse(t + 1, t + m + 1);
	while(m && t[m] == '0') m --;
	
	if(!m) {
		rep(i, 1, n) if(s[i] == '1') return puts("-1"), void();
		return puts("0"), void();
	}
	reverse(t + 1, t + m + 1);
	
	rep(i, 1, k - m) if(s[i] == '1') return puts("-1"), void();
	
	int ans = 0;
	rep(i, k - m + 1, n - m + 1) if(s[i] == '1') {
		ans ++;
		rep(j, 1, m) if(t[j] == '1') s[i + j - 1] = ('0' + (s[i + j - 1] == '0'));
	}
	rep(i, n - m + 2, n) if(s[i] == '1') return puts("-1"), void();
	printf("%d\n", ans);
}

int main() {
	int t = read(); while(t --) solve(); return 0;
}