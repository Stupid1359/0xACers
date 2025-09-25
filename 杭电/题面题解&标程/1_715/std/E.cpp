#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a < b) swap(a, b);
        LL prod = LL(a + b) * (a - b);
        printf("%lld\n", max(prod - 1, 0LL) / 2 + max(prod - 4, 0LL) / 4);
    }
    return 0;
}
