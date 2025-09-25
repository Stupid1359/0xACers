//1¡Ük¡Ün¡Ü1e9,0¡ÜS,T¡Ün,t¡Ü2e5
#include<bits/stdc++.h>
using namespace std;using ll=long long;
using ull=unsigned long long;using ld=long double;
using pii=pair<int,int>;using pll=pair<ll,ll>;using pdd=pair<ld,ld>;
using vi=vector<int>;using vl=vector<ll>;using vvi=vector<vector<int>>;
clock_t tcl;void toS(){tcl=clock();}void toT(char c=':'){cout<<"Time"<<c<<double(clock()-tcl)<<'\n';}
const int M=1e9+7;const ll inf=1e17;const ld eps=1e-10;
struct S
{	
	int n,k,S,T,ans=M;
    void solve()
	{
        cin>>n>>k>>S>>T;int K=min(k,n-k)*2;
        for(int z=0;z<2;z++)
        {
            int L=S,R=S,x=0;if(z)L=0+abs(S-k),R=n-abs((n-S)-k);
            if((L-T)%2)continue;if(!K){if(L==T)ans=min(ans,z);continue;}
            if(T<L)x=(L-T+K-1)/K;else if(T>R)x=(T-R+K-1)/K;ans=min(ans,x*2+z);
        }
        if(ans==M)ans=-1;cout<<ans<<'\n';
	}
};
void precal()
{
   
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	precal();int t=1;cin>>t;
	while(t--){S SS;SS.solve();}
}