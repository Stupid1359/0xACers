#include<bits/stdc++.h>
typedef long long LL;
typedef unsigned long long ULL;
typedef __int128 BIG;
#define rep(i, a, b) for(int i = (a); i <= (b); i ++)
#define per(i, a, b) for(int i = (a); i >= (b); i --)
using namespace std;

BIG n, w, ans, cur, tim, now;

inline BIG read() {
	BIG x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? -1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f; 
}

void print(BIG x) {
    if(!x) return;
    print(x / 10);
    putchar((x % 10) + '0');
}

BIG calc(BIG L, BIG R) {
	return (R - L + 1) * (L + R) / 2;
}

void solve() {
	n = read();
    w = read();
	ans = 0, cur = 1, tim = 0;
	
	while(n >= w) {
		tim += 1;
		now = n / w;
		ans += calc(cur, cur + now - 1) * tim;
		n -= now;
		cur += now;
	}
	
	tim += 1;
	ans += calc(cur, cur + n - 1) * tim;
	
	if(!ans) puts("0"); else print(ans), putchar('\n');
}

int main() {
	int t; cin >> t; while(t --) solve(); return 0;
}