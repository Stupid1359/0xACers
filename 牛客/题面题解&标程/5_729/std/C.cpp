#include<bits/stdc++.h>
using namespace std;using ll=long long;using i128=__int128;using ull=unsigned long long;using ld=long double;
using pii=pair<int,int>;using pll=pair<ll,ll>;using pdd=pair<ld,ld>;
using vi=vector<int>;using vl=vector<ll>;using vvi=vector<vector<int>>;
clock_t tcl;void toS(){tcl=clock();}void toT(char c=':'){cout<<"Time"<<c<<double(clock()-tcl)<<'\n';}
const int M=998244353;const ll inf=1e17;const ld eps=1e-10;
struct S
{	
	int n,q;vector<ll>a;
    ll ss(int l,int r){if(l>r)return 0;return a[r]-a[l-1];}
	void solve()
	{
        cin>>n;a.resize(n+1);
        for(int i=1,x;i<=n;i++)cin>>x,a[i]=a[i-1]+x;
        cin>>q;while(q--)
        {
            ll s;cin>>s;
            int sl=1,sr=n,L=0,R=n;
            while(R-L>1){int m=L+R>>1;(ss(sl+m,sr-m)<=s)?R=m:L=m;}sl+=L,sr-=L;
            L=0,R=sr-sl+1;while(R-L>1){int m=L+R>>1;(ss(sl+m,sr)<=s)?R=m:L=m;}if(L&1){cout<<"Alice\n";continue;}
            L=0,R=sr-sl+1;while(R-L>1){int m=L+R>>1;(ss(sl,sr-m)<=s)?R=m:L=m;}if(L&1){cout<<"Alice\n";continue;}
            cout<<"Bob\n";
        }
	}
};
void precal()
{

}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	precal();int t=1;//cin>>t;
	while(t--){S SS;SS.solve();}
}