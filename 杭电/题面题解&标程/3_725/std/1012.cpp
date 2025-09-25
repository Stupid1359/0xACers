#include<bits/stdc++.h>
using namespace std;using ll=long long;using pii=pair<int,int>;using ull=unsigned long long;
const int M=1e9+7,inv2=(M+1)/2;
void add(ll&a,ll b){a+=b;if(a>=M)a-=M;}
struct btb
{
    int n,m;ll res=0;
    void Sol2(vector<pii>&v)
    {
        ll sc=0,sw=0,sd=0,sdw=0;int lst=0;
        for(auto [p,w]:v)
        {
            ll d=ll(p)-lst;lst=p;//d=3e9 warning
            add(sd,sc*d%M);add(sdw,sw*d%M);
            add(res,(w*sd+sdw)%M);
            sc++,add(sw,w);
        }
    }
    vector<pii>rA,rB;
    void solve()
    {
        cin>>n;
        for(int i=0,x,y,w;i<n;i++)
        {
            cin>>x>>y>>w;
            rA.push_back({x+y,w});
            rB.push_back({x-y,w});
        }
        sort(rA.begin(),rA.end());Sol2(rA);
        sort(rB.begin(),rB.end());Sol2(rB);
        cout<<res*inv2%M<<'\n';
    }
};
signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t=1;cin>>t;
    while(t--){btb RR;RR.solve();}
}