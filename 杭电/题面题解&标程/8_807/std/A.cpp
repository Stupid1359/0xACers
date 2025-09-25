#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
static const int maxl = 23;

int tricks;

void solve() {
    static char s[maxl];
    scanf("%s", s);
    int n = strlen(s), p;
    s[n + 1] = '1';
    if(s[0] == '-') {
        for(p = 1; p < n && s[p] <= '1'; ++p);
    } else {
        for(p = 0; p < n && s[p] >= '1'; ++p);
    }
    rotate(s + p, s + n + 1, s + n + 2);
    puts(s);
    tricks |= 1 << ((p == n) << 1 | (s[0] == '-'));
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: ", Case);
        solve();
    }
    {
        static const int maxp = 4;
        static char msk[5];
        for(int i = 0, tp = tricks; i < maxp; ++i, tp >>= 1)
            msk[i] = "01"[tp & 1];
        msk[maxp] = '\0';
        fprintf(stderr, "tricks: %s\n", msk);
    }
    return 0;
}
