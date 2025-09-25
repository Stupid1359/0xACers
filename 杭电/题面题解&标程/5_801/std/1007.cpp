#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

void solve() {
    int n, k;
    scanf("%d%d", &n, &k);
    int ans = k * power(n - k + 1, mod - 2) % mod;
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) solve();
}