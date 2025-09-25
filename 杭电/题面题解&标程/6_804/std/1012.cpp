#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long f[1<<19],g[1<<19],fntt[1<<19],gntt[1<<19],prodntt[1<<19],prod[1<<19],wi[20],winv[20],trans[1<<19],invv;
long long qpow(long long a,long long b){
	long long ans=1;
	while(b>0)
	{
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void ntt(int t){
	int i,j,k;
	long long x,u,v;
	for(i=0;i<(1<<t);i++)
	{
		fntt[i]=f[trans[i]];
		gntt[i]=g[trans[i]];
	}
	for(i=0;i<t;i++)
	{
		for(j=0;j<(1<<t);j+=(1<<(i+1)))
		{
			x=1;
			for(k=0;k<(1<<i);k++)
			{
				u=fntt[j+k];
				v=fntt[j+k+(1<<i)]*x%mod;
				x*=wi[t-i-1];
				x%=mod;
				fntt[j+k]=(u+v)%mod;
				fntt[j+k+(1<<i)]=(u-v+mod)%mod;
			}
		}
		for(j=0;j<(1<<t);j+=(1<<(i+1)))
		{
			x=1;
			for(k=0;k<(1<<i);k++)
			{
				u=gntt[j+k];
				v=gntt[j+k+(1<<i)]*x%mod;
				x*=wi[t-i-1];
				x%=mod;
				gntt[j+k]=(u+v)%mod;
				gntt[j+k+(1<<i)]=(u-v+mod)%mod;
			}
		}
	}
	for(i=0;i<(1<<t);i++)prodntt[i]=fntt[i]*gntt[i]%mod;
	for(i=0;i<(1<<t);i++)prod[i]=prodntt[trans[i]]*invv%mod;
	for(i=0;i<t;i++)
	{
		for(j=0;j<(1<<t);j+=(1<<(i+1)))
		{
			x=1;
			for(k=0;k<(1<<i);k++)
			{
				u=prod[j+k];
				v=prod[j+k+(1<<i)]*x%mod;
				x*=winv[t-i-1];
				x%=mod;
				prod[j+k]=(u+v)%mod;
				prod[j+k+(1<<i)]=(u-v+mod)%mod;
			}
		}
	}
}
int precalc(int n,int m){
	int i,j,t,mem;
	long long w;
	for(t=0;(1<<t)<n+m-1;t++);
	invv=qpow((1<<t),mod-2);
	for(i=0;i<(1<<t);i++)
	{
		f[i]=0;
		g[i]=0;
		fntt[i]=0;
		gntt[i]=0;
		prod[i]=0;
		prodntt[i]=0;
		trans[i]=0;
	}
	for(i=0;i<(1<<t);i++)
	{
		mem=i;
		for(j=0;j<t;j++)
		{
			if(mem>=(1<<(t-j-1)))
			{
				trans[i]+=(1<<j);
				mem-=(1<<(t-j-1));
			}
		}
	}
	w=qpow(3,(mod-1)/(1<<t));
	wi[0]=w;
	winv[0]=qpow(w,mod-2);
	for(i=1;i<t;i++)
	{
		wi[i]=wi[i-1]*wi[i-1]%mod;
		winv[i]=winv[i-1]*winv[i-1]%mod;
	}
	return t;
}
long long a[200000],vis[200001],inv[200001],pw4[200001],tt[200001];
vector<long long>v[200000][2],tv[200000][2];
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T;
	long long n,i,j,t,c,s,w,ans,cur;
	inv[1]=1;
	for(i=2;i<=200000;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	tt[0]=1;
	pw4[0]=1;
	for(i=1;i<=200000;i++)
	{
		tt[i]=tt[i-1]*i%mod;
		pw4[i]=pw4[i-1]*4%mod;
	}
	for(cin>>T;T>0;T--)
	{
		cin>>n;
		for(i=1;i<=n;i++)vis[i]=0;
		for(i=0;i<n;i++)
		{
			cin>>a[i];
			if(a[i]!=-1)vis[a[i]]=1;
		}
		c=0;
		for(i=1;i<=n;i++)
		{
			if(!vis[i])
			{
				v[c][0].push_back(1);
				v[c][1].push_back(i);
				v[c][0].push_back((i+inv[i])%mod);
				v[c][1].push_back(0);
				c++;
			}
		}
		s=c;
		if(c==0)
		{
			v[0][0].push_back(1);
			v[0][1].push_back(0);
			c++;
		}
		while(c>1)
		{
			for(i=1;i<c;i+=2)
			{
				t=precalc(v[i-1][0].size(),v[i][0].size());
				for(j=0;j<v[i-1][0].size();j++)f[j]=v[i-1][0][j];
				for(j=0;j<v[i][0].size();j++)g[j]=v[i][0][j];
				ntt(t);
				for(j=0;j<v[i-1][0].size()+v[i][0].size()-1;j++)tv[i/2][0].push_back(prod[j]);
				t=precalc(v[i-1][0].size(),v[i][1].size());
				for(j=0;j<v[i-1][0].size();j++)f[j]=v[i-1][0][j];
				for(j=0;j<v[i][1].size();j++)g[j]=v[i][1][j];
				ntt(t);
				for(j=0;j<v[i-1][0].size()+v[i][1].size()-1;j++)tv[i/2][1].push_back(prod[j]);
				t=precalc(v[i-1][1].size(),v[i][0].size());
				for(j=0;j<v[i-1][1].size();j++)f[j]=v[i-1][1][j];
				for(j=0;j<v[i][0].size();j++)g[j]=v[i][0][j];
				ntt(t);
				for(j=0;j<v[i-1][1].size()+v[i][0].size()-1;j++)tv[i/2][1][j]=(tv[i/2][1][j]+prod[j])%mod;
			}
			if(c%2==1)
			{
				tv[c/2][0]=v[c-1][0];
				tv[c/2][1]=v[c-1][1];
			}
			for(i=0;i<c;i++)
			{
				v[i][0].clear();
				v[i][1].clear();
			}
			c=(c+1)/2;
			for(i=0;i<c;i++)
			{
				swap(v[i][0],tv[i][0]);
				swap(v[i][1],tv[i][1]);
			}
		}
		w=1;
		ans=0;
		c=0;
		for(i=0;i<n;i++)
		{
			if(a[i]!=-1)
			{
				if(i==0)w=w*a[i]%mod;
				else w=(w*(a[i]+inv[a[i]]))%mod;
			}
			else c++;
			if(i==n-1)cur=w;
			else cur=w*2*pw4[n-2-i]%mod;
			cur=cur*tt[s-c]%mod;
			if(a[0]==-1)cur=cur*tt[c-1]%mod;
			else cur=cur*tt[c]%mod;
			if(a[0]==-1)ans=(ans+cur*v[0][1][c-1])%mod;
			else ans=(ans+cur*v[0][0][c])%mod;
		}
		v[0][0].clear();
		v[0][1].clear();
		cout<<ans*qpow(pw4[n-1]*tt[s]%mod,mod-2)%mod<<'\n';
	}
	return 0;
}
