#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
using ll = long long;
const int N = 200050;

int n, m, k, p;
int a[N];

bool check(ll mid) {
    ll cnt = 0;
    vector<ll> vec;
    for (int i = 1; i <= n; i++) {
        if (a[i] >= mid * k)
            cnt += mid;
        else
            cnt += a[i] / k, vec.push_back(a[i] % k);
    }
    if (cnt >= mid * p) return mid * p * k >= m;
    ll sum = cnt * k;
    for (int i = 0; i < min(mid * p - cnt, (ll)vec.size()); i++)
        sum += vec[i];
    return sum >= m;
}

void solve() {
    scanf("%d%d%d%d", &n, &m, &k, &p);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1, [](auto x, auto y) {
        return x % k > y % k;
    });
    int L = 1, R = 1e9, ans = 1e9;
    while (L <= R) {
        int mid = (L + R) / 2;
        if (check(mid))
            ans = mid, R = mid - 1;
        else
            L = mid + 1;
    }
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}