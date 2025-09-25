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
const int p=998244353;
ll ksm(int a,int b){ll ans=1,bs=a;while(b){if(b&1)ans=ans*bs%p;bs=bs*bs%p;b>>=1;}return ans;}
mt19937 rd(time(0));
#define reaD read
vector<int> e[5005];
ll f[5005][5005][2];
int siz[5005];
ll fac[5005],inv[5005],g[5005];
ll C(int n,int m)
{
    if(n<m||m<0)return 0;
    return fac[n]*inv[m]%p*inv[n-m]%p;
}
ll invC(int n,int m)
{
    if(n<m||m<0)return 0;
    return inv[n]*fac[m]%p*fac[n-m]%p;
}
void dfs(int x,int fa)
{
    siz[x]=1;
    f[x][1][1]=1;
    f[x][0][0]=1;
    for(auto o:e[x])
    {
        if(o==fa)continue;
        dfs(o,x);
        for(int i=siz[x]+siz[o];i>=1;i--)
        for(int j=max(1,i-siz[x]);j<=siz[o]&&j<=i;j++)
        {
            f[x][i][1]=(f[x][i][1]+f[x][i-j][1]*f[o][j][0])%p;
            f[x][i][0]=(f[x][i][0]+f[x][i-j][0]*(f[o][j][0]+f[o][j][1]))%p;
        }
        siz[x]+=siz[o];
    }
}
int main()
{
    fac[0]=1;
    for(int i=1;i<=5000;i++)fac[i]=fac[i-1]*i%p;
    inv[5000]=ksm(fac[5000],p-2);
    for(int i=4999;i>=0;i--)inv[i]=inv[i+1]*(i+1)%p;
    int n=read();
    for(int i=1;i<n;i++)
    {
        int x=reaD(),y=reaD();
        e[x].pb(y);
        e[y].pb(x);
    }
    dfs(1,1);
    ll ans=0;
    for(int i=0;i<=n;i++)
    g[i]=(f[1][i][0]+f[1][i][1])%p,g[i]=fac[n-i]%p*fac[i]%p*g[i]%p;
    for(int i=n-1;i>=0;i--)
    {
        // cout<<i<<" "<<g[i]<<endl;
        ans=(ans+(n-i)*(g[i]-g[i+1]+p))%p;
    }
    printf("%lld\n",ans*inv[n]%p);
    return 0;
}
/*
5
1 2
2 3
3 4
2 5
598946615

3
1 2
2 3
665496237
*/