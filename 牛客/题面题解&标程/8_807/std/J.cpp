#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int BLEN = 24, BMSK = (1 << BLEN) - 1, EMSK = BMSK / 3, OMSK = EMSK << 1;
const int maxn = (int)2e5 + 9, maxl = (maxn - 1) / (BLEN << 1) + 1;

struct Decimal {
    vector<int> a, b;
    pair<int, int> parseOne(int n, char s[]) {
        int res[2] = {}, o = 0;
        for(int i = 0; i < n; ++i, o = !o)
            res[o] = -res[o] << 1 | (s[i] == '1');
        return {res[!o], res[o]};
    }
    void parse() {
        a.clear();
        b.clear();

        static char s[maxn];
        scanf("%s", s);
        int n = strlen(s), fir = n % (BLEN << 1), u, v;
        if(fir > 0) {
            tie(u, v) = parseOne(fir, s);
            a.push_back(u);
            b.push_back(v);
        }
        for( ; fir < n; fir += BLEN << 1) {
            tie(u, v) = parseOne(BLEN << 1, s + fir);
            a.push_back(u);
            b.push_back(v);
        }
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        shrink_to_fit();
    }
    void shrink_to_fit() {
        for( ; !a.empty() && !a.back(); a.pop_back());
        for( ; !b.empty() && !b.back(); b.pop_back());
    }
    int size() const {
        return max(a.size(), b.size());
    }
    int reduceOne(LL &v) const {
        int r = v & BMSK;
        v = (v - r) >> BLEN;
        if(r > EMSK) {
            ++v;
            r -= 1 << BLEN;
        }
        return r;
    }
    Decimal operator * (Decimal const &t) const {
        int sz = size(), tsz = t.size(), len = sz + tsz - 1;
        LL va = 0, vb = 0;
        Decimal res;
        res.a.reserve(len + 2);
        res.b.reserve(len + 2);
        for(int i = 0; i < len; ++i) {
            for(int j = max(i - tsz + 1, 0), k = i - j; k >= 0; ++j, --k) {
                // (a * t.a - b * t.b * 2, a * t.b + b * t.a)
                int aL = j < a.size() ? a[j] : 0, bL = j < b.size() ? b[j] : 0;
                int aR = k < t.a.size() ? t.a[k] : 0, bR = k < t.b.size() ? t.b[k] : 0;
                va += (LL)aL * aR - 2LL * bL * bR;
                vb += (LL)aL * bR + (LL)aR * bL;
            }
            res.a.push_back(reduceOne(va));
            res.b.push_back(reduceOne(vb));
        }
        while(va || vb) {
            res.a.push_back(reduceOne(va));
            res.b.push_back(reduceOne(vb));
        }
        res.shrink_to_fit();
        return res;
    }
    void print() const {
        int sz = size(), len = 0;
        static char buf[maxn];
        for(int i = 0, o, val[2]; i < sz; ++i) {
            val[0] = i < a.size() ? a[i] : 0;
            val[1] = i < b.size() ? b[i] : 0;
            for(o = 0; val[0] || val[1]; o = !o) {
                buf[len++] = "01"[val[o] & 1];
                val[o] = -((val[o] - (val[o] & 1)) >> 1);
            }
            if(i + 1 < sz)
                for(o = (i + 1) * (BLEN << 1); len < o; buf[len++] = '0');
        }
        reverse(buf, buf + len);
        if(!len)
            buf[len++] = '0';
        buf[len] = '\0';
        puts(buf);
    }
    void debug() const {
        int sz = size();
        printf("%d:\n", sz);
        for(int i = 0; i < sz; ++i)
            printf("%d ", i < a.size() ? a[i] : 0);
        puts("");
        for(int i = 0; i < sz; ++i)
            printf("%d ", i < b.size() ? b[i] : 0);
        puts("");
    }
} A, B, C;

void solve() {
    A.parse();
    B.parse();
    // A.debug();
    // B.debug();
    C = A * B;
    // C.debug();
    C.print();
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
