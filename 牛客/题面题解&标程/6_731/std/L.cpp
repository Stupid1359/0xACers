#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<cstdio>
#include<cctype>
#include<vector>
#include<bitset>
#include<random>
#include<ctime>
#include<queue>
#include<cmath>
#include<list>
#include<map>
#include<set>
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define pll pair<long long,long long>
#define FF fflush(stdout)
#define inf 0x3f3f3f3f
#define endl "\n"
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
//char buf[1<<20],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int s=0,f=1;
    char x=getchar();
    while(!isdigit(x))f=(x=='-'?-1:1),x=getchar();
    while(isdigit(x))s=s*10+x-'0',x=getchar();
    return s*f;
}
const int p=1e9+7;
//ll ksm(int a,int b){ll ans=1,bs=a;while(b){if(b&1)ans=ans*bs%p;bs=bs*bs%p;b>>=1;}return ans;}
mt19937 rd(time(0));
#define reaD read
pii d[100005];
bool a[200005];
int main()
{
    int T=read();
    while(T--)
    {
        int n=read(),m=read();
        for(int i=1;i<=2*n;i++)
        a[i]=0;
        for(int i=1;i<=m;i++)
        {
            int l=read(),r=read();
            d[i]=mp(l,r);
        }
        sort(d+1,d+m+1);
        int mi=1e9;
        int cnt=0;
        for(int i=m;i>=1;i--)
        {
            if(d[i].se<mi)
            mi=d[i].fi,cnt++,a[mi]=1;
        }
        if(cnt>n)
        {
            puts("-1");
            continue;
        }
        int s=0;
        bool ok=1;
        for(int i=1;i<=2*n;i++)
        {
            if(!a[i]&&cnt<n)
            a[i]=1,cnt++;
            if(a[i])s++;
            else s--;
            if(s<0)
            {
                ok=0;
                break;
            }
        }
        if(!ok)
        {
            puts("-1");
            continue;
        }
        assert(s==0);
        for(int i=1;i<=2*n;i++)
        {
            putchar(a[i]?'(':')');
        }
        puts("");
    }
    return 0;
}
/*
3
2 2
1 2
3 4
3 4
1 1
2 2
3 3
4 4
5 3
2 4
3 9
7 10
*/