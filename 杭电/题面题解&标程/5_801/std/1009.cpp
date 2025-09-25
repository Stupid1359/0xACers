#include <bits/stdc++.h>
using namespace std;

const int N = 500050;
int n, a[N], b[N], pos[N];

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]), pos[b[i]] = i;
    int ans = 0;
    for (int i = 1, j = pos[a[i]]; i < n; i++) {
        if (pos[a[i + 1]] != j + 1) {
            ans++;
            j = pos[a[i + 1]];
            continue;
        } else
            j++;
    }
    printf("%d\n", ans + 1);
}

int main() {
    int t = 1;
    scanf("%d", &t);
    while (t--) solve();
    return 0;
}