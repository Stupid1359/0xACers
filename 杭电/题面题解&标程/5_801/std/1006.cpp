#include <cstdio>
using namespace std;
int SG(long long n, bool is_path) {
    if (is_path) {
        if (n == 3) return 2;
        switch (n % 4) {
            case 0:
                return 0;
            case 1:
                return 1;
            case 2:
                return 1;
            case 3:
                return 3;
        }
    } else {
        if (n % 4 == 3 || n == 2) {
            return 1;
        }
        return 0;
    }
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        long long ans = 0;
        while (n--) {
            int b;
            long long a;
            scanf("%lld %d", &a, &b);
            ans ^= SG(a, b);
            // printf("%d\n", SG(a,b));
        }
        if (ans) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}