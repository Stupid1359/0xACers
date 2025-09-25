#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef __int128_t LLL;
#define N 1000 + 5
#define Q 1000000 + 5
#define M 2097152 + 5
#define ls(x) x << 1
#define rs(x) x << 1 | 1

int n, q, A[N], T[N], L[N], R[N], OrdL[N], OrdR[N], W[N], D[Q], Ord[Q];
LL SumL[N], SumR[N], Ans[Q];
vector<pair<LL, LL>> Tree[M];

struct Line
{
    int lhs, rhs;
    LL k, b;
    Line() {}
    Line(int lhs, int rhs, LL k, LL b) : lhs(lhs), rhs(rhs), k(k), b(b) {}
    bool operator < (const Line& obj) const
    {
        return make_pair(k, -b) < make_pair(obj.k, -obj.b);
    }
};
vector<Line> lines;

struct Frac
{
    LL fz, fm;
    Frac() : Frac(0, 1) {}
    Frac(LL fz, LL fm) : fz(fz), fm(fm) {}
    bool operator < (const Frac& obj) const
    {
        return LLL(fz) * obj.fm < LLL(fm) * obj.fz;
    }
};

int Rank(int d)
{
    int l = 1, r = q + 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (D[Ord[mid]] < d)
            l = mid + 1;
        else r = mid;
    }
    return l;
}

void Add(int x, int l, int r, int s, int t, LL k, LL b)
{
    if (l == s && r == t)
    {
        Tree[x].emplace_back(make_pair(k, b));
        return;
    }
    int mid = (l + r) >> 1;
    if (t <= mid)
        Add(ls(x), l, mid, s, t, k, b);
    else if (s > mid)
        Add(rs(x), mid + 1, r, s, t, k, b);
    else
    {
        Add(ls(x), l, mid, s, mid, k, b);
        Add(rs(x), mid + 1, r, mid + 1, t, k, b);
    }
}

inline Frac GetX(const pair<LL, LL> &lhs, const pair<LL, LL> &rhs)
{
    return Frac(lhs.second - rhs.second, rhs.first - lhs.first);
}

void Query(int x, int l, int r)
{
    vector<Frac> X;
    vector<pair<LL, LL>> S;
    for (const pair<LL, LL>& p : Tree[x])
    {
        if (S.empty())
            S.emplace_back(p);
        else
        {
            if (S.back().first == p.first)
                continue;
            for (; S.size() > 1 && GetX(S.back(), p) < X.back(); )
            {
                S.pop_back();
                X.pop_back();
            }
            X.emplace_back(GetX(S.back(), p));
            S.emplace_back(p);
        }
    }

    if (!S.empty())
    {
        for (int i = l, j = 0; i <= r; i ++)
        {
            for (; j < (int)X.size() && X[j] < Frac(D[Ord[i]], 1); j ++) ;
            Ans[Ord[i]] = max(Ans[Ord[i]], S[j].first * D[Ord[i]] + S[j].second);
        }
    }

    if (l == r) return ;
    int mid = (l + r) >> 1;
    Query(ls(x), l, mid);
    Query(rs(x), mid + 1, r);
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i ++)
    {
        scanf("%d", A + i);
        T[i] = A[i];
    }
    for (int i = 1; i < n; i ++)
    {
        scanf("%d", W + i);
        OrdL[i] = OrdR[i] = i;
    }
    for (int i = 1; i <= q; i ++)
    {
        scanf("%d", D + i);
        Ord[i] = i;
    }
    sort(T + 1, T + n + 1);
    sort(Ord + 1, Ord + q + 1, [](int u, int v) {
        return D[u] < D[v];
    });
    sort(OrdL + 1, OrdL + n, [](int u, int v) {
        return min(A[u], A[u + 1]) < min(A[v], A[v + 1]);
    });
    sort(OrdR + 1, OrdR + n, [](int u, int v) {
        return max(A[u], A[u + 1]) < max(A[v], A[v + 1]);
    });
    for (int i = 1; i < n; i ++)
    {
        SumL[i] = SumL[i - 1] + W[OrdL[i]];
        SumR[i] = SumR[i - 1] + W[OrdR[i]];
        L[i] = min(A[OrdL[i]], A[OrdL[i] + 1]);
        R[i] = max(A[OrdR[i]], A[OrdR[i] + 1]);
    }
    for (int i = 1; i <= n; i ++)
    {
        LL base_ans = 0;
        for (int u = 0, v = 0, ptr = i; ptr <= n; ptr ++)
        {
            for (; u < n - 1 && L[u + 1] <= T[ptr]; u ++) ;
            for (; v < n - 1 && R[v + 1] <= T[ptr]; v ++) ;
            int mn_d = T[ptr] - T[i] + 1;
            int mx_d = ptr < n ? T[ptr + 1] - T[i] : D[Ord[q]];
            if (mn_d > mx_d)
                continue;
            LL k = SumL[u] - SumR[v];
            LL b = base_ans - k * (mn_d - 1);
            base_ans = k * mx_d + b;
            if (k < 0)
                b += k * (mn_d - 1), k = 0;
            int lhs = Rank(mn_d), rhs = (k == 0 ? q : Rank(mx_d + 1) - 1);
            if (lhs <= rhs)
                lines.emplace_back(lhs, rhs, k, b);
        }
    }
    for (int j = n; j; j --)
    {
        LL base_ans = 0;
        for (int u = n - 1, v = n - 1, ptr = j; ptr >= 1; ptr --)
        {
            for (; u > 0 && L[u] >= T[ptr]; u --) ;
            for (; v > 0 && R[v] >= T[ptr]; v --) ;
            int mn_d = T[j] - T[ptr] + 1;
            int mx_d = ptr > 1 ? T[j] - T[ptr - 1] : D[Ord[q]];
            if (mn_d > mx_d)
                continue;
            LL k = SumL[u] - SumR[v];
            LL b = base_ans - k * (mn_d - 1);
            base_ans = k * mx_d + b;
            if (k < 0)
                b += k * (mn_d - 1), k = 0;
            int lhs = Rank(mn_d), rhs = (k == 0 ? q : Rank(mx_d + 1) - 1);
            if (lhs <= rhs)
                lines.emplace_back(lhs, rhs, k, b);
        }
    }
    sort(lines.begin(), lines.end());
    for (const Line& line : lines)
        Add(1, 1, q, line.lhs, line.rhs, line.k, line.b);
    Query(1, 1, q);
    for (int i = 1; i <= q; i ++)
        printf("%lld\n", Ans[i]);
    return 0;
}
