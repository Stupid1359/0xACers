#include <bits/stdc++.h>
using namespace std;using ll=long long;using pii=pair<int,int>;using ull=unsigned long long; 
const int M=1e9+7,V=5e5+10,P=1<<19,B=1e6,K=B*2+5;const ll inf=1e17;
struct dot
{
    int id,vU,vD;ll w;
    bool operator<(const dot&e)const{return w>e.w;}
};
vector<dot>xuy[K],xdyub[K];
int lit_u[K],lit_d[K],tc;
void opErr(string s){cout<<"Err:"<<s<<'\n';exit(0);}
struct S
{
    int n,m,k;
    vector<int>y,x,w;
    vector<ll>dis[2];
    priority_queue<dot>eDq;vector<int>vlu,vld;
    void add_dot(int id,int x,int y,int w)
    {
        if(y<1||y>n)return;int vU=x+y,vD=x-y+B;dot A={id,vU,vD,w};if(x<=2){eDq.push(A);return;}
        if(lit_u[vU]^tc)lit_u[vU]=tc,vlu.push_back(vU);xuy[vU].push_back(A);
        if(lit_d[vD]^tc)lit_d[vD]=tc,vld.push_back(vD);xdyub[vD].push_back(A);
    }
    void solve()
    {
        tc++;cin>>n>>m>>k;y=x=w=vector<int>(k+1,-1);dis[0]=dis[1]=vector<ll>(k+1,inf);
        for(int i=1;i<=k;i++){cin>>y[i]>>x[i]>>w[i];for(int ny=y[i]-1;ny<=y[i]+1;ny++)add_dot(i,x[i],ny,w[i]);}
        for(auto vU:vlu){auto&v=xuy[vU];sort(v.begin(),v.end(),[&](dot a,dot b){return a.vD>b.vD;});}
        for(auto vD:vld){auto&v=xdyub[vD];sort(v.begin(),v.end(),[&](dot a,dot b){return a.vU>b.vU;});}
        while(!eDq.empty())
        {
            auto [id,vU,vD,w]=eDq.top();eDq.pop();int se=vU&1;
            ll&d=dis[se][id];
            if(d==inf)
            {
                d=w;
                for(int ny=y[id]-1;ny<=y[id]+1;ny++)
                {
                    int vU2=x[id]+ny,vD2=x[id]-ny+B;
                    if((vU2-vU)%2==0)eDq.push({id,vU2,vD2,d});
                }
            }      
            int x=(vU+vD-B)/2;if(x>=m-1){dis[se][0]=min(dis[se][0],d);continue;}
            {
                auto&v=xuy[vU+2];
                while(!v.empty()&&v.back().vD<=vD+2)
                {
                    auto nd=v.back();v.pop_back();
                    nd.w=min(nd.w+d,dis[se][nd.id]);eDq.push(nd);
                }
            }
            {
                auto&v=xdyub[vD+2];
                while(!v.empty()&&v.back().vU<=vU+2)
                {
                    auto nd=v.back();v.pop_back();
                    nd.w=min(nd.w+d,dis[se][nd.id]);eDq.push(nd);
                }
            }
        }
        for(auto vU:vlu)xuy[vU].clear();
        for(auto vD:vld)xdyub[vD].clear();
        for(int z=0;z<2;z++)
        {
            ll v=dis[z][0];if(v==inf)v=-1;
            cout<<v<<" \n"[z==1];
        }
    }
};
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t=1;cin>>t;
    while(t--){S SS;SS.solve();}
}