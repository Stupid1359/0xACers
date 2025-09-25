#include<bits/stdc++.h>
using namespace std;using ll=long long;const int M=998244353;
ll poww(ll bs,ll x){ll res=1;for(bs%=M;x;x>>=1,(bs*=bs)%=M)if(x&1)(res*=bs)%=M;return res;}
ll invv(ll bs){return poww(bs,M-2);}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	ll n,m,p;cin>>n>>m>>p;if(p==1){for(int i=0;i<=m;i++)cout<<n<<" \n"[i==m];return 0;}
	ll sp=(poww(invv(p),n)-1),A=invv(M+1-p)*(M-p)%M;
	for(ll i=0,dot,sum,ans=0;i<=m;i++)
	{
		if(!i)
		{
			dot=poww(p,n-1);
			sum=(poww(p,n)+M-1)*invv(p+M-1)%M;			
		}
		else
		{
			dot=dot*(n-1+i)%M*invv(i)%M*(M+1-p)%M;
			(sum+=dot*A)%=M;
		}
		(ans+=sum)%=M;
		cout<<(ans+sp*sum%M)%M<<" \n"[i==m];
	}
}