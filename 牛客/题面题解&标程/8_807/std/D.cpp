#include<bits/stdc++.h>
using namespace std;
const int MAXN=105;
const int INF=0x3f3f3f3f;
const int Mod=1000000007;
struct Data
{
    int v,c;
    explicit Data(int _v=-INF,int _c=0):v(_v),c(_c){}
    Data operator + (const Data& rhs)const
    {
        if(v>rhs.v)return *this;
        if(v<rhs.v)return rhs;
        return Data(v,(c+rhs.c)%Mod);
    }
    Data operator * (const Data& rhs)const
    {
        return Data(v+rhs.v,1LL*c*rhs.c%Mod);
    }
    Data& operator += (const Data& rhs)
    {
        return *this=*this+rhs;
    }
};
vector<pair<int,int>> e[MAXN];
int a[MAXN],b[MAXN],sz[MAXN],son[MAXN],sc[MAXN];
void hld(int u,int fa)
{
    sz[u]=1,son[u]=0;
    for(auto& [v,c] : e[u])
    {
        if(v==fa)continue;
        hld(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]])
            son[u]=v,sc[u]=c;
    }
}
array<vector<Data>,3> rdp[MAXN];
array<vector<Data>,3> dfs(int u,int fa,const vector<Data>& pdp,bool full)
{
    int m=(int)pdp.size();
    array<vector<Data>,3> dp;
    if(!son[u])dp={pdp,vector<Data>(m),pdp};
    else
    {
        auto sdp=dfs(son[u],u,pdp,full);
        for(int i=0;i<3;i++)
            dp[i].resize(m);
        for(int i=0;i<m;i++)
        {
            dp[0][i]+=sdp[0][i]+sdp[1][i]+sdp[2][i];
            dp[1][i]+=sdp[0][i];
            dp[2][(i+sc[u])%m]+=sdp[1][i];
        }
    }
    for(auto& [v,c] : e[u])
    {
        if(v==fa || v==son[u])continue;
        array<vector<Data>,3> vdp[3];
        for(int i=0;i<3;i++)
            vdp[i]=dfs(v,u,dp[i],false);
        array<vector<Data>,3> tdp;
        for(int i=0;i<3;i++)
            tdp[i].resize(m);
        for(int i=0;i<m;i++)
        {
            tdp[0][i]+=vdp[0][0][i]+vdp[0][1][i]+vdp[0][2][i];
            tdp[1][i]+=vdp[1][0][i]+vdp[2][0][i];
            tdp[1][(i+c)%m]+=vdp[1][1][i];
            tdp[2][(i+c)%m]+=vdp[2][1][i];
        }
        dp.swap(tdp);
    }
    for(int i=1;i<3;i++)
    {
        vector<Data> tmp(m);
        for(int j=0;j<m;j++)
            tmp[(j+a[u])%m]+=dp[i][j]*Data(b[u],1);
        dp[i].swap(tmp);
    }
    if(full)
    {
        rdp[u]=dp;
        for(auto& [v,c] : e[u])
        {
            if(v==fa || v==son[u])continue;
            dfs(v,u,pdp,true);
        }
    }
    return dp;
}
int main()
{
    int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i],&b[i]);
    for(int i=1;i<=n;i++)
        e[i].clear();
    for(int i=1;i<n;i++)
    {
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        e[u].emplace_back(v,c);
        e[v].emplace_back(u,c);
    }
    hld(1,0);
    vector<Data> init(m);
    init[0]=Data(0,1);
    dfs(1,0,init,true);
    for(int i=1;i<=q;i++)
    {
        int r,k;
        scanf("%d%d",&r,&k);
        auto res=rdp[r][0][k]+rdp[r][1][k];
        if(r!=1)res+=rdp[r][2][k];
        printf("%d %d\n",max(res.v,-1),res.c);
    }
    return 0;
}
