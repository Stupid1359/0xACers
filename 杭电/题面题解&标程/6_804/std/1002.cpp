#include<bits/stdc++.h>
using namespace std;
const long long inf=1000000000000000000LL;
long long cnt[1000001],cntsum[1000001],sumddis[1000001],sumdseg[1000001];
long long gcd(long long a,long long b){
	return b>0?gcd(b,a%b):a;
}
long long chkans1(long long p,long long m){
	long long i,ans=cnt[p];
	for(i=p;i<=m;i+=p)ans+=(cntsum[min(i+p,m)]-cntsum[i])*(i/p+1);
	return ans;
}
long long chkseg(long long l,long long r,long long d,long long m){
	long long disx=(r-l+1)/d,rx=disx*d+l-1,ans;
	if(r<l)return 0;
	ans=(cntsum[r]-cntsum[rx])*(disx+1);
	ans+=sumdseg[l];
	if(rx<m)
	{
		ans-=sumdseg[rx+1];
		ans-=(cntsum[m]-cntsum[rx])*disx;
	}
	return ans;
}
long long chkans2(long long p,long long d,long long m){
	long long i,ans=0;
	for(i=0;i<=m;i+=p)
	{
		if(i>0)ans+=(cntsum[min(i+p-1,m)]-cntsum[i-1])*(i/p);
		ans+=chkseg(i+1,min(i+p-1,m),d,m);
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T;
	long long n,m,i,a,ans,g,lsum,csum,mn;
	for(cin>>T;T>0;T--)
	{
		cin>>n>>m;
		for(i=0;i<=m;i++)cnt[i]=0;
		mn=inf;
		for(i=0;i<n;i++)
		{
			cin>>a;
			mn=min(mn,a);
			cnt[a]++;
		}
		cntsum[0]=0;
		for(i=1;i<=m;i++)cntsum[i]=cntsum[i-1]+cnt[i];
		for(i=m;i>=0;i--)
		{
			sumddis[i]=cnt[i];
			if(i+mn<=m)sumddis[i]+=sumddis[i+mn];
			sumdseg[i]=sumddis[i];
			if(i+1<=m)sumdseg[i]+=sumdseg[i+1];
		}
		ans=inf;
		g=0;
		lsum=0;
		for(i=1;i<=m;i++)
		{
			if(cnt[i]==0)continue;
			if(g==0)ans=min(ans,chkans1(i,m));
			else ans=min(ans,chkans1(i,m)+lsum/g);
			lsum+=i*cnt[i];
			g=gcd(g,i);
		}
		for(i=mn+1;i<=m;i++)ans=min(ans,chkans2(i,mn,m));
		cout<<ans<<'\n';
	}
	return 0;
}
