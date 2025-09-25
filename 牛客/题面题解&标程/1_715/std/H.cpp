#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long uLL;
#define N 1000000 + 5
#define S 65536

int n, q, L[S], R[S], Cnt[S];
uLL Val[N];
bool Flag[N];
char s[N];

inline uLL BitBetween(int l, int r)
{
    uLL ret = r == 63 ? -1uLL : (1uLL << (r + 1)) - 1;
    ret ^= (1uLL << l) - 1;
    return ret;
}

inline void Update(int val, uLL &ret, int &ri)
{
    ret += ri * L[val] + Cnt[val];
    ri = R[val] + (L[val] >> 4) * ri;
}

struct Bitset
{
    Bitset() : Bitset(0) {}
    Bitset(int _sz) {
        sz = _sz;
        ptr = 0;
        vec.resize((_sz + 63) >> 6);
    }
    void Add(int cnt, uLL val)
    {
        if (cnt <= 64 - (ptr & 63))
            vec[ptr >> 6] |= val << (ptr & 63);
        else
        {
            uLL mask = BitBetween(0, 64 - (ptr & 63) - 1);
            vec[ptr >> 6] |= (val & mask) << (ptr & 63);
            vec[(ptr >> 6) + 1] = val >> (64 - (ptr & 63));
        }
        ptr += cnt;
    }
    void GetSame(const Bitset& rhs)
    {
        while (sz != ptr || rhs.sz != rhs.ptr) ;
        for (int i = 0; i < vec.size(); i++)
            vec[i] ^= ~rhs.vec[i];
        int mn_sz = min(sz, rhs.sz);
        for (int i = mn_sz >> 6; i < vec.size(); i++)
        {
            int l_bit = max(0, mn_sz - (i << 6));
            int r_bit = 63;
            vec[i] &= ~BitBetween(l_bit, r_bit);
        }
    }
    uLL Calc() const
    {
        uLL ret = 0;
        for (int i = 0, ri = 0; i < vec.size(); i++)
        {
            Update(vec[i] & (S - 1), ret, ri);
            Update(vec[i] >> 16 & (S - 1), ret, ri);
            Update(vec[i] >> 32 & (S - 1), ret, ri);
            Update(vec[i] >> 48 & (S - 1), ret, ri);
        }
        return ret;
    }
    void out() const
    {
        fprintf(stderr, "sz = %d : ", sz);
        for (int i = 0; i < sz; i ++)
            fprintf(stderr, "%llu", (vec[i >> 6] >> (i & 63)) & 1);
        fprintf(stderr, "\n");
    }

    int sz, ptr;
    vector<uLL> vec;
};

Bitset GetBitset(int l, int r)
{
    Bitset ret(r - l + 1);
    if ((l >> 6) == (r >> 6))
    {
        uLL val = (Val[l >> 6] & BitBetween(l & 63, r & 63)) >> (l & 63);
        ret.Add(r - l + 1, val);
    }
    else
    {
        uLL val = (Val[l >> 6] & BitBetween(l & 63, 63)) >> (l & 63);
        ret.Add(63 - (l & 63) + 1, val);
        for (int i = (l >> 6) + 1; i < (r >> 6); i ++)
            ret.Add(64, Val[i]);
        val = Val[r >> 6] & BitBetween(0, r & 63);
        ret.Add((r & 63) + 1, val);
    }
    return ret;
}

int main()
{
    for (int x = 0; x < S; x ++)
    {
        for (int i = 0; i < 16; i ++)
        {
            if ((x >> i) & 1)
                L[x] ++;
            else break ;
        }
        for (int i = 0; i < 16; i ++)
        {
            if ((x >> (15 - i)) & 1)
                R[x] ++;
            else break ;
        }
        for (int i = 0, j = 0; i < 16; i ++)
        {
            j = ((x >> i) & 1) ? j + 1 : 0;
            Cnt[x] += j;
        }
    }
    scanf("%d%d", &n, &q);
    scanf("%s", s);
    for (int i = 0; i < n; i += 64)
    {
        uLL val = 0;
        for (int j = 0; j < 64 && i + j < n; j ++)
            val |= uLL(s[i + j] - '0') << j;
        Val[i >> 6] = val;
    }
    for (int i = 1, op, l, r, a, b; i <= q; i ++)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d%d", &l, &r);
            l --, r --;
            if ((l >> 6) == (r >> 6))
            {
                Val[l >> 6] ^= BitBetween(l & 63, r & 63);
            }
            else
            {
                Val[l >> 6] ^= BitBetween(l & 63, 63);
                Val[r >> 6] ^= BitBetween(0, r & 63);
                Flag[(l >> 6) + 1] ^= 1;
                Flag[r >> 6] ^= 1;
            }
        }
        else
        {
            for (int b = 0, pre = 0; (b << 6) < n; b ++)
            {
                Flag[b] ^= pre;
                if (Flag[b])
                    Val[b] ^= -1uLL;
                pre = Flag[b];
                Flag[b] = 0;
            }
            scanf("%d%d%d", &l, &a, &b);
            a --, b --;
            Bitset u = GetBitset(a, a + l - 1), v = GetBitset(b, b + l - 1);
            u.GetSame(v);
            uLL ans = u.Calc();
            printf("%llu\n", ans);
        }
    }
    return 0;
}
