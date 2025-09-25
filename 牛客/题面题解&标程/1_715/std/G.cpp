#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 100000 + 5

int n, q;
char s[N], t[N];

int main()
{
    scanf("%d%d", &n, &q);
    scanf("%s", s + 1);
    for (int i = 1, a; i <= q; i ++)
    {
        scanf("%s%d", t + 1, &a);
        LL ans = 0;
        for (int j = 1, pre = 0; t[j]; j ++)
        {
            if (t[j] == s[a + j - 1])
                pre ++;
            else pre = 0;
            ans += pre;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
