#include <bits/stdc++.h>

using namespace std;
#define cs const
#define pb push_back
#define ll long long
//$f[i]=(1-p_i)*i+p_i*(f[i+1]+20)$

cs int N = 100005;
double p[N], f[N];
int n;
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            p[i] = 1.0 * x / 1000;
        }
        f[n] = n;
        for (int i = n - 1; i >= 1; i--) {
            f[i] = min((1 - p[i]) * i + p[i] * (f[i + 1] + 20), f[i + 1]);
        }
        printf("%.10lf\n", f[1]);
    }
    return 0;
}