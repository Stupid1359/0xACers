#include <bits/stdc++.h>

using s64 = long long;

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

const int N = 19010;

int n;
int a[N];

void work() {
    std::cin >> n;

    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }

    s64 cost = 1e18;
    int x = -1;

    for (int i = 2; i <= std::min(n, 1'900); i += 2) {
        s64 cur_cost = (1ll * (i + n) * (n - i - 1) / 2) / i + 1ll * (n - i) * i + 1ll * (i - 2) * (i * 2 + 1);
        if (cost > cur_cost) {
            cost = cur_cost;
            x = i;
        }
    }

    std::vector<int> ans;

    auto upd = [&] (int l) {
        std::rotate(a + l, a + l + 1, a + l + x);
        ans.push_back(l);
    };

    for (int i = n; i >= x; i --) {
        int u = std::find(a + 1, a + 1 + n, i) - a;

        for (; u + x - 1 <= i; u += x - 1) {
            upd(u);
        }

        if (u != i) {
            for (; u >= i - x + 1; u --) {
                upd(i - x + 1);
            }
        }
    }

    for (int i = 1; i < x; i ++) {
        int p = std::find(a + 1, a + x, i) - a;

        if (p != i) {
            for (int j = 1; j <= p - i - 1; j ++) {
                upd(i + 1);
            }

            upd(i + 1);

            for (int j = 1; j <= x; j ++) {
                upd(i + (j & 1));
            }

            for (int j = 1; j <= x - (p - i - 1); j ++) {
                upd(i + 1);
            }
        }
    }

    assert(ans.size() <= 1'900'000);

    std::cout << x << '\n';
    std::cout << ans.size() << '\n';
    for (int l : ans) {
        std::cout << l << ' ';
    }
    std::cout << '\n';
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