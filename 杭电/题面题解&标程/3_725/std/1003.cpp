#include<bits/stdc++.h>
using namespace std;using ll=long long;using pii=pair<int,int>;using ull=unsigned long long;using ld=long double;
clock_t tcl;void toS(){tcl=clock();}void toT(char c=':'){cout<<"Time"<<c<<double(clock()-tcl)<<'\n';}
const int M=1e9+7,N=1e6+10;const ll inf=1e17;
struct calcC{//precal needed
	ll poww(ll bs,ll x){ll res=1;for(bs=(bs%M+M)%M;x;x>>=1,(bs*=bs)%=M)if(x&1)(res*=bs)%=M;return res;}
	ll invv(ll bs){return poww(bs,M-2);}vector<ll>mul,inv;
	void precal(int P){mul.resize(P+1);mul[0]=1;for(int i=1;i<=P;i++)mul[i]=mul[i-1]*i%M;
		inv.resize(P+1);inv[P]=invv(mul[P]);for(int i=P;i;i--)inv[i-1]=inv[i]*i%M;}
	ll C(int n,int m){if(n==-1&&m==-1)return 1;if(n<m||m<0)return 0;return mul[n]*inv[m]%M*inv[n-m]%M;}
	ll A(int n,int m){if(n<m||m<0)return 0;return mul[n]*inv[n-m]%M;}
}xC;
struct b2b
{	
	int n,m;ll a,b,c,bas,db,res=0;
	void solve()
	{
		cin>>n>>m>>a>>b;c=a+b;n+=2;
		if(b==0){cout<<bool(m==0)<<'\n';return;}if(a==0){cout<<bool(n==m+1)<<'\n';return;}
		bas=xC.poww(a*xC.invv(c)%M,n+m-1);db=xC.poww(b*xC.invv(a)%M,2);
		for(int z=0,lim=min(n,m);z<=lim;z++,(bas*=db)%=M)(res+=bas*xC.C(n-1,z)%M*xC.C(m-1,z-1)%M)%=M;
		cout<<res<<'\n';
	}
};
void precal(){xC.precal(N);}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	precal();
	int t=1;cin>>t;
	while(t--){b2b RR;RR.solve();}
}