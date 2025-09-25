#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
static const int maxn = (int)1e5 + 9;

void solve() {
    int n, H;
    static pair<int, int> a[maxn];
    scanf("%d%d", &n, &H);
    for(int i = 0; i < n; ++i) {
        auto &[h, o] = a[i];
        scanf("%d", &h);
        h = min(h, H - h);
        o = i + 1;
    }
    sort(a, a + n);
    for(int i = 0; i < n; ++i)
        printf("%d%c", a[i].second, " \n"[i == n - 1]);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: ", Case);
        solve();
    }
    return 0;
}
