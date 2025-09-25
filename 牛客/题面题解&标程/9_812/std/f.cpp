#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve() {
    int sx1, sy1, sx2, sy2, tx1, ty1, tx2, ty2;
    cin >> sx1 >> sy1 >> sx2 >> sy2 >> tx1 >> ty1 >> tx2 >> ty2;
    int sx = sx1 + sx2, sy = sy1 + sy2;
    int tx = tx1 + tx2, ty = ty1 + ty2;
    cout << max(abs(sx - tx), abs(sy - ty)) << '\n';
}

signed main() {
    cin.sync_with_stdio(false), cin.tie(0);
    int T; cin >> T;
    while(T--) solve();
    return 0;
}