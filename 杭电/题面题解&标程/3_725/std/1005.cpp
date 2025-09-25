#include<bits/stdc++.h>
using namespace std;using ll=long long;const int M=998244353,N=1e7;
struct calcC{//precal needed
	ll poww(ll bs,ll x){ll res=1;for(bs=(bs%M+M)%M;x;x>>=1,(bs*=bs)%=M)if(x&1)(res*=bs)%=M;return res;}
	ll invv(ll bs){return poww(bs,M-2);}vector<ll>mul,inv;
	void precal(int P){mul.resize(P+1);mul[0]=1;for(int i=1;i<=P;i++)mul[i]=mul[i-1]*i%M;
		inv.resize(P+1);inv[P]=invv(mul[P]);for(int i=P;i;i--)inv[i-1]=inv[i]*i%M;}
	ll C(int n,int m){if(n<m)return 0;return mul[n]*inv[m]%M*inv[n-m]%M;}}xC;
struct CC
{
	vector<set<int>>es[2];int n,tc=0,siz,cnt=0,c2=0;
	vector<pair<int,int>>arr;vector<int>tim;
	vector<int>lit;
	bool spr2(int x,int lst,bool se)
	{		
		for(auto k:es[se][x])if(k!=lst)
		{
			if(tim[k]==tc)return 0;tim[k]=tc;
			if(!spr2(k,x,se))return 0;
		}
		return 1;
	}
	bool chk()
	{
		for(int e=0;e<2;e++)
		{
			tc++;for(int i=1;i<=n;i++)if(tim[i]!=tc)
				{tim[i]=tc;if(!spr2(i,0,e))return 0;}
		}	
		return 1;	
	}
	void spr(int pos)
	{
		if(pos==siz){cnt+=chk();return;}
		int a=arr[pos].first,b=arr[pos].second;
		for(int e=0;e<2;e++)
		{
			es[e][a].insert(b),es[e][b].insert(a);			
			lit[pos]=e;spr(pos+1);
			es[e][a].erase(b),es[e][b].erase(a);
		}
	}
	int calc(int _n)
	{
		n=_n;for(int e=0;e<2;e++)es[e].resize(n+1);tim.resize(n+1,0);arr.clear();
		for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)arr.push_back({i,j});
		siz=n*(n-1)/2;lit.resize(siz,0);spr(0);return cnt;
	}
};
struct btb
{
	int n,P=6;vector<ll>tran,dp;
	void ini()
	{
		tran.resize(P+1);for(int i=1;i<=P;i++){CC Cw;tran[i]=Cw.calc(i)*xC.inv[i]%M;}
		dp.resize(N+1);dp[0]=1;for(int i=1;i<=N;i++)for(int j=1;j<=min(i,5);j++)(dp[i]+=dp[i-j]*tran[j]%M)%=M;
	}
	void solve()
	{		
		ini();int q;cin>>q;for(int i=1,x;i<=q;i++)cin>>x,cout<<dp[x]*xC.mul[x]%M<<'\n';
	}
};
int main()
{	
	ios::sync_with_stdio(0);cin.tie(0);xC.precal(N);
	int t=1;while(t--){btb RR;RR.solve();}		
}