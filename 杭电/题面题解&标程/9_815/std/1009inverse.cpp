#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned ll;
const ll Mod=998244353;
ll fpw(ll x,ll y,ll m=Mod){
	ll res=1,cur=x;
	for(ll i=1;i<=y;i<<=1){
		if(i&y)res=res*cur%m;
		cur=cur*cur%m;
	}
	return res;
}
ll inv(ll x,ll p){
	return fpw(x,p-2,p);
}
ll T,p;
int main(){
	for(scanf("%lld",&T);T;T--){
		scanf("%lld",&p);
		ll k=(p+118)/119;
		if(k>=23){
			ll ixor=0,pw2=fpw(2,k);
			for(ll i=(p-1)/4*4; i<p; i++)
				ixor^=i;
			ll middle=(pw2*pw2+pw2)%Mod *(ixor%Mod) %Mod;
			ll last=(p%Mod)*((p-2)%Mod)+2;
			printf("%lld\n", (middle+last)%Mod);
		}
		else{
			ull ans=0;
			for(ull i=1;i<(ull)p;i++)
				ans^= (inv(i,p)+(1ull<<k))*(i+(1ull<<2*k));
			printf("%lld\n",(long long)(ans%Mod));
		}
	}
	return 0;
}
