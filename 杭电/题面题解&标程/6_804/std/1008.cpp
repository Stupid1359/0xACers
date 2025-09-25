#include <bits/stdc++.h>
using namespace std;
long long val[1<<13],cval[1<<13],l2[1<<13],dp[14][1<<13],a[13];
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T,n,m,k,i,j,t;
    long long cur;
    for(i=0;i<13;i++)l2[1<<i]=i;
    for(cin>>T;T>0;T--)
    {
    	cin>>n>>m>>k;
    	k=min(k,m);
    	for(i=0;i<(1<<m);i++)val[i]=0;
		for(j=0;j<n;j++)
		{
			for(i=0;i<m;i++)cin>>a[i];
			for(i=1;i<(1<<m);i++)
			{
				cval[i]=cval[i&(i-1)]+a[l2[i-(i&(i-1))]];
				val[i]=max(val[i],cval[i]);
			}
		}
		for(j=0;j<=k;j++)
		{
			for(i=0;i<(1<<m);i++)dp[j][i]=0;
		}
		for(j=0;j<k;j++)
		{
			for(i=0;i<(1<<m);i++)
			{
				for(t=(1<<m)-i-1;t>0;t=((t-1)&((1<<m)-i-1)))dp[j+1][i+t]=max(dp[j+1][i+t],dp[j][i]+val[t]);
			}
		}
		cout<<dp[k][(1<<m)-1]<<'\n';
	}
    return 0;
}
