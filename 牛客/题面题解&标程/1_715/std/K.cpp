#include <bits/stdc++.h>
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
    vector<int> vis(2*m+1),cov(m+1),num(cnt+1);
    for(int i=1; i<=2*m; i++)
    {
        if(vis[i])continue;
        int eid=i,cid=bel[i];
        for(int j=1; j<=siz[cid]; j++)
        {
            vis[eid]=1;
            if(!cov[(eid-1)%m+1])
            {
                ++num[cid];
                cov[(eid-1)%m+1]=1;
            }
            eid=lst.nxt[eid];
        }
        for(int j=1; j<=siz[cid]; j++)
        {
            cov[(eid-1)%m+1]=0;
            eid=lst.nxt[eid];
        }
    }
    for(int i=1; i<=n; i++)
        printf("%d\n",num[bel[get_eid(e[i][0],0)]]);
    return 0;
}
