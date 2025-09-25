#include<bits/stdc++.h>
using namespace std;
int p[200002],pos[200002],dp[200002],tre[200010],N,inf=1000000000;
int lowbit(int x){
	return x-(x&(x-1));
}
void add(int p,int vl){
	for(;p<=N;p+=lowbit(p))tre[p]=min(tre[p],vl);
}
int qry(int p){
	int vl=inf;
	for(;p>0;p-=lowbit(p))vl=min(vl,tre[p]);
	return vl;
}
void clr(){
	int i;
	for(i=0;i<=N;i++)tre[i]=inf;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T,n,i,c,ans;
	for(cin>>T;T>0;T--)
	{
		cin>>n;
		for(i=1;i<=n;i++)
		{
			cin>>p[i];
			pos[p[i]]=i;
		}
		p[0]=0;
		pos[0]=0;
		p[n+1]=n+1;
		pos[n+1]=n+1;
		n+=2;
		N=n;
		clr();
		for(i=0;i<n;i++)dp[i]=inf;
		dp[0]=0;
		for(i=0;i<n;i++)
		{
			if(i>0&&pos[i]>pos[i-1])dp[i]=min(dp[i],dp[i-1]);
			dp[i]=min(dp[i],qry(pos[i])+i);
			add(pos[i]+1,dp[i]-i);
		}
		cout<<dp[n-1]<<'\n';
	}
	return 0;
}
