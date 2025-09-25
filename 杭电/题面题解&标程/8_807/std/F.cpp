#include<bits/stdc++.h>
using namespace std;
const int MAXD=10;
const int MAXL=58;
const int msk[MAXD|1]={119,36,93,109,46,107,123,37,127,111};
vector<int> sub;
void dfs(int u,int led,int& res,const vector<int>& val)
{
    if(u==0)
    {
        static bool vis[1<<21|1];
        bool isok=1;
        for(auto v : val)isok&=!vis[v&led],vis[v&led]=1;
        for(auto v : val)vis[v&led]=0;
        if(isok)res=min(res,__builtin_popcount(led));
        return;
    }
    for(int i=0;i<(int)sub.size();i++)
        dfs(u-1,led<<7|sub[i],res,val);
}
int solve()
{
    int n,m;
    scanf("%d%d",&n,&m);
    vector<int> val(n);
    for(int i=0;i<n;i++)
    {
        static char buf[7];
        scanf("%s",buf);
        for(int j=0;j<m;j++)
            val[i]=val[i]<<7|msk[buf[j]-'0'];
    }
    int res=7*m;
    dfs(m,0,res,val);
    return 0*printf("%d\n",res);
}
void prepare()
{
    map<vector<int>,int> mp;
    for(int i=0;i<128;i++)
    {
        map<int,int> vis;
        vector<int> idx(MAXD);
        for(int j=0;j<MAXD;j++)
        {
            if(!vis[msk[j]&i])
                vis[msk[j]&i]=vis.size();
            idx[j]=vis[msk[j]&i];
        }
        if(!mp.count(idx) || __builtin_popcount(i)<__builtin_popcount(mp[idx]))
            mp[idx]=i;
    }
    vector<pair<vector<int>,int>> vec(mp.begin(),mp.end());
    for(size_t i=0;i<vec.size();i++)
    {
        bool isok=1;
        for(size_t j=0;j<vec.size() && isok;j++)
        {
            if(i==j)continue;
            bool subdiv=1;
            for(int x=0;x<MAXD && subdiv;x++)
                for(int y=x+1;y<MAXD && subdiv;y++)
                    if(vec[i].first[x]!=vec[i].first[y])
                        subdiv&=(vec[j].first[x]!=vec[j].first[y]);
            if(subdiv)isok&=__builtin_popcount(vec[i].second)<__builtin_popcount(vec[j].second);
        }
        if(isok)sub.push_back(vec[i].second);
    }
}
int main()
{
    prepare();
    int T;
    scanf("%d",&T);
    while(T--)solve();
    return 0;
}
