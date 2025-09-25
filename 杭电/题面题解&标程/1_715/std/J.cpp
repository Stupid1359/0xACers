#include<bits/stdc++.h>
using namespace std;
const int MAXN=200005;
const int MAXM=600005;
struct LinkedList
{
    int pre[MAXM],nxt[MAXM];
    void init(int n)
    {
        for(int i=1; i<=n; i++)
            pre[i]=nxt[i]=i;
    }
    void link(int u,int v)
    {
        nxt[u]=v,pre[v]=u;
    }
    void cut(int u,int v)
    {
        nxt[u]=u,pre[v]=v;
    }
} lst;
vector<pair<int,int>> e[MAXN];
int ev[MAXM],bel[MAXM],siz[MAXM];
int main()
{
    int n,m=0;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
        int d;
        scanf("%d",&d);
        m+=d;
        e[i].resize(d);
        for(int j=0; j<d; j++)
        {
            scanf("%d",&e[i][j].first);
            e[i][j].second=0;
        }
    }
    m/=2;
    for(int i=1, t=0; i<=n; i++)
        for(size_t j=0; j<e[i].size(); j++)
        {
            if(e[i][j].second)continue;
            int k=e[i][j].first;
            for(size_t l=0; l<e[k].size(); l++)
                if(e[k][l].first==i)
                {
                    e[i][j].second=++t;
                    ev[t]=k;
                    e[k][l].second=t+m;
                    ev[t+m]=i;
                    break;
                }
        }
    auto get_eid=[&](const pair<int,int>& edge,int rev)
    {
        return (edge.second-1)%m+1+(((edge.second-1)/m)^rev)*m;
    };
    lst.init(2*m);
    fill(bel+1,bel+2*m+1,0);
    fill(siz+1,siz+2*m+1,0);
    int cnt=0;
    for(int i=1; i<=2*m; i++)
    {
        if(bel[i])continue;
        ++cnt;
        for(int cur=i; !bel[cur];)
        {
            bel[cur]=cnt,++siz[cnt];
            int v=ev[cur],eid=(cur-1)%m+1,nxt=0;
            for(size_t j=0; j<e[v].size(); j++)
                if((e[v][j].second-1)%m+1==eid)
                {
                    nxt=get_eid(e[v][(j+1)%e[v].size()],0);
                    break;
                }
            assert(nxt);
            lst.link(cur,nxt);
            cur=nxt;
        }
    }
    int mxc=0;
    for(int i=1; i<=cnt; i++)
        if(siz[i]>siz[mxc])mxc=i;
    assert(mxc);
    auto flip=[&](int v)
    {
        for(size_t i=0; i<e[v].size(); i++)
            lst.cut(get_eid(e[v][i],1),get_eid(e[v][(i+1)%e[v].size()],0));
        reverse(e[v].begin(),e[v].end());
        for(size_t i=0; i<e[v].size(); i++)
            lst.link(get_eid(e[v][i],1),get_eid(e[v][(i+1)%e[v].size()],0));
    };
    auto relabel=[&](int s,int t)
    {
        while(1)
        {
            --siz[bel[s]];
            bel[s]=mxc;
            ++siz[bel[s]];
            if(s==t)break;
            s=lst.nxt[s];
        }
    };
    auto adjust=[&](int v)
    {
        if(e[v].size()<3)return 0;
        vector<int> cid;
        for(size_t i=0; i<e[v].size(); i++)
            cid.push_back(bel[get_eid(e[v][i],1)]);
        if(cid[0]==cid[1] && cid[0]==cid[2])return 0;
        if(cid[0]!=cid[1] && cid[0]!=cid[2] && cid[1]!=cid[2])
        {
            for(size_t i=0; i<e[v].size(); i++)
                if(cid[i]!=mxc)relabel(get_eid(e[v][(i+1)%e[v].size()],0),get_eid(e[v][i],1));
            flip(v);
            return 1;
        }
        int dif=-1;
        for(size_t i=0; i<e[v].size(); i++)
            if(cid[i]==cid[(i+1)%e[v].size()])
                dif=(i+2)%e[v].size();
        assert(dif>=0);
        if(cid[dif]==mxc)
        {
            auto& edge=e[v][(dif+2)%e[v].size()];
            relabel(get_eid(edge,0),get_eid(edge,1));
            flip(v);
            return 1;
        }
        return 0;
    };
    int eid=0;
    for(int i=1; i<=2*m; i++)
        if(bel[i]==mxc)eid=i;
    assert(eid);
    for(int i=1; i<=siz[mxc]; i++)
    {
        adjust(ev[eid]);
        eid=lst.nxt[eid];
    }
    for(int i=1; i<=n; i++)
    {
        int t=-1;
        for(size_t j=0; j<e[i].size(); j++)
            if(bel[get_eid(e[i][j],0)]==mxc)t=j;
        assert(t>=0);
        for(size_t j=0; j<e[i].size(); j++)
            printf("%d%c",e[i][(j+t)%e[i].size()].first, " \n"[j+1==e[i].size()]);
    }
    return 0;
}
