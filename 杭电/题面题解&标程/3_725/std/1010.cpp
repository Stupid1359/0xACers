#include<bits/stdc++.h>
using namespace std;using ll=long long;
const int M=998244353;
ll poww(ll bs,ll x){ll res=1;for(;x;x>>=1,(bs*=bs)%=M)if(x&1)(res*=bs)%=M;return res;}
ll invv(ll bs){return poww(bs,M-2);}
struct node{ll c,a,sz,fx;}Bas={1,1,1,0},Zero={0,0,0,0};
node mg(node&A,node&B)
{
    node C;C.c=(A.c*B.c)%M;
    C.a=(A.a*B.c+A.c*B.a+A.sz*B.sz*2)%M;
    C.sz=(A.sz*B.c+B.sz*A.c)%M;
    C.fx=(A.fx*B.c+B.fx*A.c)%M;
    return C;
}
node ct(node&A,node&B)
{
    node C;C.c=(A.c*B.c)%M;
    C.a=(A.a*B.c)%M;
    C.sz=(A.sz*B.c)%M;
    C.fx=(A.fx*B.c+B.fx*A.c+B.a*A.c)%M;
    return C;
}
void add(node&A,node&B)
{
    (A.c+=B.c)%=M;(A.a+=B.a)%=M;(A.sz+=B.sz)%=M;(A.fx+=B.fx)%=M;
}
struct btb
{
    int n,k;vector<vector<int>>es;
    ll G(node A)
    {
        return (A.a+A.fx)*invv(A.c)%M;
    }
    vector<node> spr(int x,int lst)
    {
        int nowsiz=0;vector<node>V(1,Bas);
        for(auto y:es[x])if(y!=lst)
        {
            auto v=spr(y,x);int siz2=v.size()-1;
            int bord=min(nowsiz+siz2+1,k);
            vector<node>R(bord+1,Zero);
            for(int a=0;a<=nowsiz;a++)for(int b=0,lim=min(siz2,bord-a);b<=lim;b++)
            {
                node C=mg(V[a],v[b]);add(R[a+b],C);
                if(a+b<bord)C=ct(V[a],v[b]),add(R[a+b+1],C);
            }
            swap(V,R);nowsiz=bord;
        }
        return V;
    }
    void solve()
    {
        cin>>n>>n>>k;es.resize(n+1);
        for(int i=1,u,v;i<n;i++)cin>>u>>v,es[u].push_back(v),es[v].push_back(u);
        auto v=spr(1,0);for(int i=0;i<=k;i++)cout<<G(v[i])<<" \n"[i==k];
    }
};
signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t=1;cin>>t;
    while(t--){btb RR;RR.solve();}
}