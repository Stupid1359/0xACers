#include<bits/stdc++.h>
using namespace std;using ll=long long;const int N=1e6+10;const ll inf=1e17;
struct btb
{
	int n,pt=0,pv=0;ll sum=0,ans=0;vector<int>c,cnt,val;vector<ll>dp;
	int fx(int v)
	{
		int v2=max(v,0);
		while(pt<v2)pv-=cnt[pt],pt++;
		while(pt>v2)pt--,pv+=cnt[pt];
		if(v>=0)cnt[pt]++,pv++;return pv;
	}
	void solve()
	{
		cin>>n;
        c.resize(n+1,0),cnt=val=c;dp.resize(n+2,-inf);dp[0]=0;
		for(int i=1,x;i<=n;i++)cin>>x,c[i]=i-x,sum+=abs(c[i]);
		for(int i=n;i;i--)val[i]=fx(c[i])*2-(n-i+1);
		for(int i=1;i<=n;i++)if(c[i]>0)
		{
            int x=c[i];dp[x]=max(dp[x],dp[x-1]+val[i]),ans=max(ans,dp[x]);
		}
		cout<<sum-ans<<'\n';
	}
};
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	int t=1;cin>>t;
	while(t--){btb RR;RR.solve();}
}