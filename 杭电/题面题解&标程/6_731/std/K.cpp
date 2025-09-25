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
int a[100005],b[100005];
int n;
vector<int> d[100005];
int c[100005];
int sol()
{
    int g=0;
    int tot=0;
    for(int i=1;i<n;i++)
    b[i]=abs(a[i+1]-a[i]),g=__gcd(g,b[i]),tot+=(b[i]>0);
    if(g==0)
    return 0;
    for(auto o:d[a[1]])
    c[o]=0;
    for(int i=1;i<n;i++)
    {
        for(auto o:d[b[i]])
        {
            c[o]++;
        }
    }
    for(auto o:d[a[1]])
    {
        if(o<=g)return g;
        if(c[o]>=tot-1)
        return o;
        if(c[o]>=tot-2&&a[n]%o==0)
        return o;
    }
    assert(0);
}
int main()
{
    for(int i=1;i<=100000;i++)
    for(int j=i;j<=100000;j+=i)
    d[j].pb(i);
    // int mx=0,id=0;
    // for(int i=1;i<=100000;i++)
    // {
    //     if(d[i].size()>mx)
    //     {
    //         mx=d[i].size();
    //         id=i;
    //     }
    // }
    // cout << "Max divisors: " << mx << " for number: " << id << endl;
    for(int i=1;i<=100000;i++)
    reverse(d[i].begin(), d[i].end());
    int T=read();
    while(T--)
    {
        n=read();
        for(int i=1;i<=n;i++)
        a[i]=read();
        int ans=sol();
        reverse(a+1,a+n+1);
        ans=max(ans,sol());
        printf("%d\n",ans);
    }
    return 0;
}
/*
5
2
114 514
1
2
5
1 2 3 5 8
5
4 3 3 3 4
5
6 1 4 7 9
*/