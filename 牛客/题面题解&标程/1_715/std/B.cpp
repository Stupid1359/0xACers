#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=200005;
struct SAM
{
    int n,last,cnt;
    int fa[MAXN<<1],go[MAXN<<1][2],len[MAXN<<1];
    int v[MAXN],q[MAXN<<1],pos[MAXN<<1];
    void init()
    {
        n=cnt=0,last=++cnt;
        memset(go[last],0,sizeof(go[last]));
    }
    void extend(int c)
    {
        int p=last,np=last=++cnt;
        memset(go[np],0,sizeof(go[np]));
        len[np]=len[p]+1;
        pos[++n]=np;
        while(p && !go[p][c])go[p][c]=np,p=fa[p];
        if(!p)fa[np]=1;
        else
        {
            int q=go[p][c];
            if(len[p]+1==len[q])fa[np]=q;
            else
            {
                int nq=++cnt;
                len[nq]=len[p]+1;
                memcpy(go[nq],go[q],sizeof(go[q]));
                fa[nq]=fa[q];
                fa[np]=fa[q]=nq;
                while(go[p][c]==q)go[p][c]=nq,p=fa[p];
            }
        }
    }
    ll count()
    {
        for(int i=1; i<=cnt; i++)
            v[len[i]]++;
        for(int i=1; i<=n; i++)
            v[i]+=v[i-1];
        for(int i=cnt; i; i--)
            q[v[len[i]]--]=i;
        for(int i=1; i<=n; i++)
            v[i]=0;
        ll res=0;
        for(int i=1; i<=cnt; i++)
        {
            int u=q[i],f=fa[u];
            res+=len[u]-len[f];
        }
        return res;
    }
} sam;
int solve()
{
    int n;
    ll m;
    scanf("%d%lld",&n,&m);
    for(int x=1;x<=n;x++)
    {
        ll r=1LL*(x+1)*(n+1-x)-1;
        if(r>=(4*m+4)/5 && r<=6*m/5)
        {
            for(int i=1;i<=x;i++)
                printf("0");
            for(int i=x+1;i<=n;i++)
                printf("1");
            return 0*printf("\n");
        }
    }
    if(m<2*n)return 0*printf("-1\n");
    for(int k=2;k*(k-1)/2<=n;k++)
    {
        vector<int> part(k);
        for(int i=0;i<n-k*(k-1)/2;i++)
            part[i%k]++;
        string s;
        for(int i=0;i<k;i++)
        {
            for(int j=0;j<i;j++)
                s+='1';
            for(int j=0;j<part[i];j++)
                s+='0';
        }
        sam.init();
        for(auto c : s)
            sam.extend(c-'0');
        ll r=sam.count();
        if(r>=(4*m+4)/5 && r<=6*m/5)
            return 0*printf("%s\n",s.c_str());
    }
    return 0*printf("-1\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)solve();
    return 0;
}
