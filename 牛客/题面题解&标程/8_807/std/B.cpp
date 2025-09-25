#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
const int maxl = 1 << 20;
const UL BMSK = (1U << 30) - 1;

int n, len;
UL A, B, C;
char ans[maxl + 1];

inline UL rng61() {
    static UL t;
    t = A ^ ((A << 16) & BMSK);
    t ^= t >> 5;
    A = B;
    B = C;
    C = A ^ B ^ t ^ ((t << 1) & BMSK);
    // printf("rng61 %u %u %u\n", A, B, C);
    return C;
}

inline void flush() {
    if(!len)
        return;
    ans[len] = '\0';
    printf("%s", ans);
    len = 0;
}

inline void append(char const &ch) {
    ans[len++] = ch;
    if(len == maxl)
        flush();
}

void solve() {
    scanf("%d%d%d%d", &n, &A, &B, &C);
    A &= BMSK;
    B &= BMSK;
    C &= BMSK;
    bool cur = 0;
    // vector<int> perm(n);
    // iota(perm.begin(), perm.end(), 0);
    for(int i = 0; i < n; ++i) {
        int j = i + rng61() % (n - i);
        // printf("#%d: %d\n", i, j);
        cur ^= i != j;
        // swap(perm[i], perm[j]);
    }
    // for(int i = 0; i < n; ++i)
    //     printf("%d%c", perm[i], " \n"[i == n - 1]);
    append("01"[cur]);
    for(int i = 1; i < n; ++i) {
        int L = rng61() % n;
        int R = rng61() % n;
        int d = rng61() % n + 1;
        if(L > R)
            swap(L, R);
        // printf("#%d: %d %d %d\n", i, L, R, d);
        cur ^= (R - L) & d & 1;
        append("01"[cur]);
    }
    append('\n');
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case)
        solve();
    flush();
    return 0;
}
