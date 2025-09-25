#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const ll p=998244353;
const int N=1e5+5;
int n,m;
struct E{
    int to,w;
};
vector<vector<E>> G;
int rd[N];
int mx1[N],mxd[N];
int f[N][32];
ll pp[N];
int cmp(ll x,ll dx,ll y,ll dy){
    if(!x)return 1;
    if(!y)return 0;
    if(dx==dy)return x<y;
    if(dx<dy)return cmp(y,dy,x,dx)^1;
    x*=dy,y*=dx;
    if(dx-dy>30)return 0;
    __int128_t z=(__int128_t)y-((__int128_t)x<<dx-dy);
    if(z<=0)return 0;
    if(dy>=30)return 1;
    return ((__int128_t)(y-x)<((__int128_t)z<<dy))?1:0;
}
ll qs(ll x,ll y){
    ll z=1;
    while(y){
        if(y&1)z=z*x%p;
        x=x*x%p,y>>=1;
    }
    return z;
}
int ay[N];
int lz[N];
void dp(int y,int d,int w){
    if(w)mx1[y]=max(mx1[y],d);
    lz[d]=max(lz[d],w);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    pp[0]=1;for(int i=1;i<=100005;++i)pp[i]=pp[i-1]*2%p;
    int T;cin>>T;
    while(T--)
{
    cin>>n>>m;
    G.clear();G.resize(n+1);
    for(int i=1;i<=m;++i){
        int x,y,z;cin>>x>>y>>z;
        G[x].pb({y,z});++rd[y];
    }
    vector<int> q;
    for(int i=1;i<=n;++i)if(!rd[i]){q.pb(i);mxd[i]=0;f[i][30]=0;}
    for(int i=0;i<q.size();++i){
        int x=q[i];
        for(auto e:G[x]){
            int y=e.to,w=e.w;
            vector<int> vv;
			for(int j=mx1[y];j>=max(mx1[y]-30,0);--j){vv.pb(j);lz[j]=f[y][j-(mx1[y]-30)];}
			vv.pb(mxd[x]+1);
			dp(y,mxd[x]+1,w);
            for(int j=mx1[x];j>=mx1[x]-30;--j)
			if(j>=0)
            {
            	vv.pb(j+1);
                dp(y,j+1,f[x][j-(mx1[x]-30)]+w);
            }
            mxd[y]=max(mxd[y],mxd[x]+1);
            for(int j=mx1[y];j>=max(mx1[y]-30,0);--j)f[y][j-(mx1[y]-30)]=lz[j];
            for(auto j:vv)lz[j]=0;
            --rd[y];
            if(!rd[y])q.pb(y);
        }
    }
    int ax=0,dx=0;
    memset(ay,0,(n+2)*4);
    for(int i=1;i<=n;++i){
        for(int j=mx1[i];j>=mx1[i]-30;--j)
        if(j>=0)
		{
            ay[j]=max(ay[j],f[i][j-(mx1[i]-30)]);
        }
    }
    for(int j=n-1;j>=0;--j)
    {
        if(cmp((ll)ax,(ll)dx,(ll)ay[j],(ll)j))ax=ay[j],dx=j;
    }
    cout<<(ll)ax*(pp[dx]-1+p)%p*qs(10000,p-2)%p*qs(dx,p-2)%p<<"\n";
    memset(rd,0,(n+2)*4);
    for(int i=1;i<=n;++i)memset(f[i],0,sizeof f[i]);
    memset(mxd,0,(n+2)*4);
    memset(mx1,0,(n+2)*4);
}
    return 0;
}
