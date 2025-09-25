#include <cstdio>
using namespace std;
const int mod = 1e9 + 7;
int n, m;
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        long long a = 1;
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            a = a * i % mod;
        }
        long long ans = 1;
        while (m--) {
            int x;
            scanf("%d", &x);
            ans = ans * a % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}