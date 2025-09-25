#include <bits/stdc++.h>
using namespace std;

int n, k;

void solve() {
    cin >> n >> k;
    int p = 1, s = 0;
    while (s + p <= n) {
        s += p;
        ++p;
    }
    if (s == n) {
        if (k == 1) {
            cout << n << '\n';
        } else {
            cout << -1 << '\n';
        }
    } else {
        int r = n - s;
        if (p % k == 0 && r % (p / k) == 0) {
            int len = p / k, x = (n - len * (len - 1) / 2 * k) / len;
            for (int i = 0; i < len; ++i) {
                cout << x + i * k << " \n"[i == len - 1];
            }
        } else {
            cout << -1 << '\n';
        }
    }
}

int main() {
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}