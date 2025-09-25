#include<bits/stdc++.h>
#define re register
#define il inline
#define ll long long
//#define int long long
#define pii pair<int,int>
#define ls ((p)<<1)
#define rs (((p)<<1)|1)
#define mid ((l+r)>>1)
#define lowbit(x) ((x)&(-(x)))
#define printc cerr<<"-----------------------------------------------------------\n"
#define yon(x) (x?cout<<"Yes\n":cout<<"No\n")
#define YoN(x) (x?cout<<"YES\n":cout<<"NO\n")
#define rep(x,qwq,qaq) for(re int (x)=(qwq);(x)<=(qaq);++(x))
#define per(x,qwq,qaq) for(re int (x)=(qwq);(x)>=(qaq);--(x))
#define dbg(x) cerr<<#x<<":"<<x<<" "
#define cend cerr<<'\n'
#define fsp(x) fixed<<setprecision(x)
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define inf 0x3f3f3f3f
#define maxn 1000010
int n,k;
int fa[maxn];
vector<int>g[maxn];
int dep[maxn];
int anc[maxn][25];
void dfs1(int u){
	anc[u][0]=fa[u];
	rep(i,1,20)anc[u][i]=anc[anc[u][i-1]][i-1];
	dep[u]=dep[fa[u]]+1;
	for(int v:g[u])dfs1(v);
}
int f[maxn];
int u,v,l,r;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n>>k;
    rep(i,2,n){
    	cin>>fa[i];
    	g[fa[i]].emplace_back(i);
	}
	dfs1(1);
	memset(f,0x3f,sizeof f);
	f[0]=f[1]=1;
	rep(i,1,k){
		cin>>u>>l>>r;
		if(f[u]!=inf)return cout<<l,0;
		int t=u,U=u;
		per(s,20,0){
			if(f[anc[t][s]]==inf)t=anc[t][s];
		}
		if(f[t]==inf)t=fa[t];
		per(s,20,0){
			if(dep[anc[u][s]]-dep[t]>r-l+1)u=anc[u][s];
		}
		if(dep[u]-dep[t]>r-l+1)u=fa[u];
		for(v=u;v!=t;v=fa[v])f[v]=l+dep[v]-dep[t]-1;
		if(f[U]!=inf)return cout<<f[U],0;
	}
	cout<<-1;
	return 0;
}