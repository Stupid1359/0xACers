#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=425;
const int MAXL=MAXN*MAXN*MAXN/6;
const ll INF=(1LL<<60)-1;
ll a[MAXN],dp[MAXL],tmp[MAXL];
ll sum(int l,int r)
{
    return a[r]-a[l-1];
}
ll& get(ll a[],int l,int r,int m)
{
    return a[r*(r-1)*(r-2)/6+m*(m-1)/2+l];
}
int solve()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]),a[i]+=a[i-1];
    for(int l=1;l<=n;l++)
        for(int r=l+1;r<=n;r++)
            for(int m=l;m<r;m++)
            {
                get(dp,l,r,m)=get(tmp,l,r,m)=INF;
                if(l==m)get(dp,l,r,m)=0;
                if(m+1==r)get(tmp,l,r,m)=0;
            }
    for(int len=2;len<=n;len++)
        for(int l=1,r=len;r<=n;l++,r++)
        {
            ll cof=__lg(sum(l,r)-1)+1;
            for(int m=l;m<r;m++)
                get(dp,l,r,m)=min(INF,get(dp,l,r,m)+get(tmp,l,r,m)+min(sum(l,m),sum(m+1,r))*cof);
            int s,t;
            for(s=l;s<r && sum(l,s)<sum(s+1,r);s++);
            for(t=r+1;t<=n && sum(l,r)>sum(r+1,t);t++);
            ll mi=INF;
            for(int k=t-1,m1=s-1,m2=s;k>r;k--)
            {
                ll cur=abs(sum(l,r)-sum(r+1,k));
                while(m1>=l && abs(sum(l,m1)-sum(m1+1,r))<=cur)
                    mi=min(mi,get(dp,l,r,m1)),m1--;
                while(m2<r && abs(sum(l,m2)-sum(m2+1,r))<=cur)
                    mi=min(mi,get(dp,l,r,m2)),m2++;
                get(dp,l,k,r)=min(get(dp,l,k,r),mi);
            }
            mi=INF;
            for(int k=t,m1=s-1,m2=s;k<=n;k++)
            {
                ll cur=abs(sum(l,r)-sum(r+1,k));
                while(m1>=l && abs(sum(l,m1)-sum(m1+1,r))<=cur)
                    mi=min(mi,get(dp,l,r,m1)),m1--;
                while(m2<r && abs(sum(l,m2)-sum(m2+1,r))<=cur)
                    mi=min(mi,get(dp,l,r,m2)),m2++;
                get(dp,l,k,r)=min(get(dp,l,k,r),mi);
            }
            for(t=l-1;t>=1 && sum(l,r)>sum(t,l-1);t--);
            mi=INF;
            for(int k=t,m1=s-1,m2=s;k>=1;k--)
            {
                ll cur=abs(sum(k,l-1)-sum(l,r));
                while(m1>=l && abs(sum(l,m1)-sum(m1+1,r))<=cur)
                    mi=min(mi,get(dp,l,r,m1)),m1--;
                while(m2<r && abs(sum(l,m2)-sum(m2+1,r))<=cur)
                    mi=min(mi,get(dp,l,r,m2)),m2++;
                get(tmp,k,r,l-1)=min(get(tmp,k,r,l-1),mi);
            }
            mi=INF;
            for(int k=t+1,m1=s-1,m2=s;k<l;k++)
            {
                ll cur=abs(sum(k,l-1)-sum(l,r));
                while(m1>=l && abs(sum(l,m1)-sum(m1+1,r))<=cur)
                    mi=min(mi,get(dp,l,r,m1)),m1--;
                while(m2<r && abs(sum(l,m2)-sum(m2+1,r))<=cur)
                    mi=min(mi,get(dp,l,r,m2)),m2++;
                get(tmp,k,r,l-1)=min(get(tmp,k,r,l-1),mi);
            }
        }
    for(int m=1;m<n;m++)
        printf("%lld%c",get(dp,1,n,m)<INF ? get(dp,1,n,m) : -1LL," \n"[m==n-1]);
    return 0;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)solve();
    return 0;
}
