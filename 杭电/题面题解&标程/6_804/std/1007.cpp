#include<bits/stdc++.h>
using namespace std;
string s;
int psum[200001],inf=1000000000;
int check(int n,int k,int p){
	int c=p/k*k,ans=p/k;
	while(k>0)
	{
		c+=k;
		if(c>n)return inf;
		ans++;
		k-=psum[max(c,p)]-psum[max(c-k,p)];
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T,n,k,i,ans;
	for(cin>>T;T>0;T--)
	{
		cin>>n>>k>>s;
		psum[0]=0;
		for(i=0;i<n;i++)psum[i+1]=psum[i]+s[i]-'0';
		ans=inf;
		for(i=0;i<n;i++)
		{
			if(s[i]=='1')ans=min(ans,check(n,k,i));
		}
		if(ans==inf)cout<<"-1\n";
		else cout<<ans<<'\n';
	}
	return 0;
}
