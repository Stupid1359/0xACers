#include<bits/stdc++.h>
using namespace std;using ll=long long;const int M=1e9+7,ivP=700000005,P=10;
ll poww(ll bs,ll x){ll res=1;for(;x;x>>=1,(bs*=bs)%=M)if(x&1)(res*=bs)%=M;return res;}
ll invv(ll bs){return poww(bs,M-2);}
ll pd[P+1],pv[P+1],iv[P+1],sp[P+1];
void add(int&a,int b){a+=b;if(a>=M)a-=M;}
struct btb
{
	void solve()
	{	
		int n,m,pt=0,sum=1;cin>>n>>m;	
		vector<int>dp(n+1,0),p(n+1,0),maxl(n+1,0);dp[0]=1;
		for(int i=1,x;i<=n;i++)cin>>p[i];
		while(m--){int l,r;cin>>l>>r;maxl[r]=max(maxl[r],l);}
		for(int i=1;i<=n;i++)
		{
			int w=p[i];if(w==P){dp[i]=sum;pt=i;continue;}
			dp[i]=sp[w]*sum%M;add(sum,dp[i]);
			while(maxl[i]>pt)add(sum,M-dp[pt++]);
		}
		for(int i=1;i<=n;i++)if(p[i]!=P)sum=1ll*sum*pv[p[i]]%M;cout<<sum<<'\n';
	}
};
void precal()
{
	//cout<<invv(10)<<"##\n";return 0;//700000005##
	for(int i=0;i<=P;i++)
	{
		pd[i]=ll(i)*ivP%M;// |:i/10
		pv[i]=(1-pd[i]+M)%M;// |:1-i/10
		iv[i]=invv(pv[i]);// |:1/(1-i/10)
		sp[i]=pd[i]*iv[i]%M;// |:(i/10)/(1-i/10)
	}
}
int main()
{	
	ios::sync_with_stdio(0);cin.tie(0);
	precal();
	int t=1;cin>>t;while(t--){btb RR;RR.solve();}	
}