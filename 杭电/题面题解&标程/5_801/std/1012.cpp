#include <algorithm>
#include <cstdio>
#include <vector>

void Solve() {
    int n;
    scanf("%d", &n);
    std::vector<long long> a(n), b(n), x(n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &x[i]);
    for (int i = 0; i < n; i++) {
        long long y;
        scanf("%lld", &y);
        a[i] = x[i] - y;
        b[i] = x[i] + y;
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    long long ans = ~(1LL << 63);
    for (int i = 1; i < n; i++) {
        ans = std::min(ans, a[i] - a[i - 1]);
        ans = std::min(ans, b[i] - b[i - 1]);
    }
    printf("%lld\n", ans);
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) Solve();
    return 0;
}
