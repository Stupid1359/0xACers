#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N=200009,mod=998244353;
inline void ad(int &x,int y){x+=y;if(x>=mod)x-=mod;}
int n,m,dp[N],sum[N],ud[N],fa[N];
bool vis[N];
vector<int> g[N],nod[N];
int dfn[N],scc[N],scnt=0,dfnc=0,low[N];
int stk[N],top;
void dfs(int u,int f){
	low[u]=dfn[u]=++dfnc;
	stk[++top]=u;
	for(int v:g[u])
		if(!dfn[v])dfs(v,u),low[u]=min(low[u],low[v]);
		else if(v!=f)low[u]=min(low[u],dfn[v]);
	if(low[u]==dfn[u]){
		++scnt;
		int v;
		do{
			v=stk[top--];
			scc[v]=scnt;
			nod[scnt].push_back(v);
		}while(u!=v);
	}
}
void dfs2(int u,int f){
	vis[u]=1;
	for(int i=0;i<(int)nod[u].size();i++){
		int p=nod[u][i];
		for(int v:g[p])if(v!=f&&scc[v]!=u)
			dfs2(scc[v],p),ad(dp[p],(sum[scc[v]]*2+mod-(dp[v]+1))%mod);
		ad(sum[u],dp[p]+1);
	}
}
void dfs3(int u,int f,int up){
	ud[u]=up;fa[u]=f;
	for(int v:nod[u])ad(up,dp[v]+1);
	ad(up,up);
	for(int i=0;i<(int)nod[u].size();i++){
		int tup=up,p=nod[u][i];
		ad(tup,mod-(dp[p]+1));
		if(!i)ad(tup,mod-ud[u]);
		for(int v:g[p])if(v!=f&&scc[v]!=u)
			dfs3(scc[v],p,(tup+mod-(sum[scc[v]]*2+mod-(dp[v]+1))%mod)%mod);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int cas;cin>>cas;
	while(cas--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)g[i].clear(),nod[i].clear(),dfn[i]=vis[i]=dp[i]=sum[i]=fa[i]=ud[i]=0;
		scnt=dfnc=top=0;
		for(int i=0,u,v;i<m;i++)cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
		for(int i=1;i<=n;i++)if(!dfn[i])dfs(i,0);
		for(int i=1;i<=scnt;i++)sort(nod[i].begin(),nod[i].end(),[&](int u,int v){
			return dfn[u]<dfn[v];
		});
		for(int i=1;i<=n;i++)if(!vis[scc[i]])dfs2(scc[i],0),dfs3(scc[i],0,0);
		int ans=0,jel=0;
		for(int i=1;i<=scnt;i++)if((int)nod[i].size()==1){
			int u=nod[i][0],f=1,tot1=0,tot2=0;
			for(int v:g[u])if(v!=fa[i]){
				int x=(sum[scc[v]]*2+mod-(dp[v]+1))%mod;
				(f*=x+1)%=mod;
				ad(tot2,tot1*x%mod);
				ad(tot1,x);
			}
			(f*=ud[i]+1)%=mod;
			ad(tot2,tot1*ud[i]%mod);
			ad(tot1,ud[i]);
			ad(ans,(f+mod-tot2+mod-1)%mod);
		}else{
			int t1=0,t2=0,fg=1;
			for(int j=0;j<(int)nod[i].size();j++){
				int u=nod[i][j],x=1;
				for(int v:g[u])if(scc[v]!=scc[u]&&v!=fa[i])
					(x*=(sum[scc[v]]*2+mod-(dp[v]+1))%mod+1)%=mod;
				if(!j)(x*=ud[i]+1)%=mod;
				(fg*=x)%=mod;
				int y=(dp[u]+1)%mod;
				if(!j)ad(y,ud[i]);
				ad(t2,t1*y%mod);
				ad(t1,y);
			}
			ad(ans,fg);
			for(int j=0;j<(int)nod[i].size();j++){
				int u=nod[i][j],x=(dp[u]+1)%mod;
				if(!j)ad(x,ud[i]);
				int tot1=t1,tot2=t2;
				ad(tot1,mod-x);
				ad(tot2,mod-tot1*x%mod);
				ad(tot1,tot1);
				int f=(tot2+tot1+1)%mod;
				for(int v:g[u])if(v!=fa[i]&&scc[u]!=scc[v]){
					int x=(sum[scc[v]]*2+mod-(dp[v]+1))%mod;
					(f*=x+1)%=mod;
					ad(tot2,tot1*x%mod);
					ad(tot1,x);
				}
				if(!j)(f*=ud[i]+1)%=mod,ad(tot2,tot1*ud[i]%mod),ad(tot1,ud[i]);
				ad(ans,(f+mod-tot2+mod-1)%mod);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}