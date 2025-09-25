#include <bits/stdc++.h>

using s64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

/* 取 min */
template <class T>
inline void chmin(T &x, const T &y) {
    if (x > y) {
        x = y;
    }
}
/* 取 max */
template <class T>
inline void chmax(T &x, const T &y) {
    if (x < y) {
        x = y;
    }
}

/* ----- ----- ----- 正文 ----- ----- ----- */

const int N = 5010;

const int mod = 1e9 + 7;

int qpow(int a, int b, int p) {
    int ans = 1;
    for (; b; b >>= 1) {
        if (b & 1) ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
    }
    return ans;
}

int n, R;
int a[N];

int inv[N];

int c[N][N];

void work() {
    std::cin >> n >> R;

    a[0] = R;
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }

    for (int i = n - 1; i >= 0; i --) {
        chmax(a[i], a[i + 1]);
    }

    for (int i = 1; i <= n; i ++) {
        inv[i] = qpow(i, mod - 2, mod);
    }

    c[n][0] = 1;
    for (int i = n - 1; i >= 0; i --) {
        for (int k = 0; k <= n - i; k ++) {
            c[i][k] = 0;
        }

        int b = 1;
        for (int k = 0; k <= n - i - 1; k ++) {
            b = 1ll * b * (a[i + 1] - k) % mod;
            b = 1ll * b * inv[k + 1] % mod;

            c[i][k + 1] = (c[i][k + 1] + c[i + 1][k]) % mod;
            c[i][k] = (c[i][k] + c[i + 1][k]) % mod;
            c[i][0] = (c[i][0] + 1ll * (mod - b) * c[i + 1][k]) % mod;
        }
    }

    int ans = 0, b = 1;
    for (int k = 0; k <= n; k ++) {
        ans = (ans + 1ll * b * c[0][k]) % mod;

        b = 1ll * b * (R - k) % mod;
        b = 1ll * b * inv[k + 1] % mod;
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T;
    std::cin >> T;
    
    while (T --) {
        work();
    }

    return 0;
}

/**
 *  心中无女人
 *  比赛自然神
 *  模板第一页
 *  忘掉心上人
**/