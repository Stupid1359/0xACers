#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1000000007;
inline int poW(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int n,m,k,S,T;
int head[100005],to[1000005],nxt[1000005],tot;
vector<int> ig[100005];
void addedge(int x,int y){
	++tot;
	to[tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
	ig[y].push_back(x);
}
int dfn[100005],low[100005],stk[100005],top;
bool instk[100005];
int belong[100005],cnt;
vector<int> vc[100005];
void dfs1(int v){
	dfn[v]=low[v]=++tot;
	instk[v]=1;
	stk[++top]=v;
	for(int e=head[v];e;e=nxt[e]){
		if(!dfn[to[e]]){
			dfs1(to[e]);
			low[v]=min(low[v],low[to[e]]);
		}else if(instk[to[e]]) low[v]=min(low[v],dfn[to[e]]);
	}
	if(dfn[v]==low[v]){
		++cnt;
		while(top){
			belong[stk[top]]=cnt;
			vc[cnt].push_back(stk[top]);
			instk[stk[top]]=0;
			--top;
			if(stk[top+1]==v) break;
		}
	}
}
bool vis[100005];
bool dfs2(int v,int t){
	vis[v]=1;
	if(v==t) return 1;
	for(int e=head[v];e;e=nxt[e])
		if(!vis[to[e]]){
			if(dfs2(to[e],t)) return 1;
		}
	return 0;
}
bool check(int x,int y){
	memset(vis,0,sizeof(vis));
	return dfs2(x,y);
}
int fa[100005];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int cnt2;
int tc;
bool vis1[100005];
bool vis2[100005];
int a[3][3],b[3][3],c[3][3];
void dfs3(int v){
	vis1[v]=1;
	for(int e=head[v];e;e=nxt[e])
		if(!vis1[to[e]]) dfs3(to[e]);
}
void dfs4(int v){
	vis2[v]=1;
	for(auto to:ig[v])
		if(!vis2[to]) dfs4(to);
}
int solve2(){
	for(int i=1;i<=n;++i) vis1[i]=vis2[i]=0;
	dfs3(S);
	dfs4(T);
	if(!vis1[T]){
		swap(S,T);
		for(int i=1;i<=n;++i) vis1[i]=vis2[i]=0;
		dfs3(S);
		dfs4(T);
	}
	for(int i=1;i<=n;++i) vis1[i]&=vis2[i],vis2[i]=0;
	for(int i=0;i<3;++i)for(int j=0;j<3;++j) a[i][j]=b[i][j]=c[i][j]=0;
	for(int i=1;i<=n;++i){
		if(vis1[i]) vis2[belong[i]]=1;
		for(auto to:ig[i]){
//			cout<<i<<" "<<to<<"\n";
			if(vis1[i]&&vis1[to]) ++a[0][0];
			else if(belong[i]==belong[to]) ++a[0][0];
			else ++a[0][1];
			if(belong[i]==belong[to]) ++a[1][0];
			else ++a[1][1];
		}
	}
	int sum=0;
	for(int i=1;i<=cnt;++i)
		if(vis2[i]) ++sum;
	a[0][2]=cnt-sum;
	a[1][2]=cnt-2;
	a[2][2]=1;
//	for(int i=0;i<3;++i){
//		for(int j=0;j<3;++j) cout<<a[(array<int,3>){0,1,2}[i]][(array<int,3>){0,1,2}[j]]<<" ";
//		cout<<"\n";
//	}
	b[0][0]=b[1][1]=b[2][2]=1;
	int K=k;
	while(K){
		if(K&1){
			for(int i=0;i<3;++i)
				for(int j=0;j<3;++j)
					for(int k=0;k<3;++k)
						c[i][k]+=b[i][j]*a[j][k];
			for(int i=0;i<3;++i)
				for(int j=0;j<3;++j)
					b[i][j]=c[i][j]%mod,c[i][j]=0;
		}
		for(int i=0;i<3;++i)
			for(int j=0;j<3;++j)
				for(int k=0;k<3;++k)
					c[i][k]+=a[i][j]*a[j][k];
		for(int i=0;i<3;++i)
			for(int j=0;j<3;++j)
				a[i][j]=c[i][j]%mod,c[i][j]=0;
		K>>=1;
	}
// [0 1 2]
	return (b[1][2]+b[2][2]*2)%mod;
}
signed main(){
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
scanf("%lld",&tc);
while(tc--){

	scanf("%lld%lld%lld",&n,&m,&k);
	S=1;T=2;
	iota(fa+1,fa+n+1,1);
	tot=0;
	for(int i=1,x,y;i<=m;++i){
		scanf("%lld%lld",&x,&y);
		addedge(x,y);
		fa[find(x)]=find(y);
	}
	cnt2=cnt=0;
	for(int i=1;i<=n;++i)
		if(fa[i]==i) ++cnt2;
/*
cnt: number of SCCs in G
cnt2: number of connected components(edges are considered as undirected) in G
*/
	top=0;
	for(int i=1;i<=n;++i)
		if(!dfn[i]) dfs1(i);
	if(k==0){
		printf("2\n");
		return 0;
	}
	if(belong[S]==belong[T]){// case 1: S and T are in the same SCC
		int ans=(poW(m,k-1)*(cnt-1)+(poW(m,k-1)-1)*poW(m-1,mod-2)%mod*(cnt2-1)%mod+1)%mod;
		printf("%lld\n",ans);
	}else{
		if(check(S,T)||check(T,S)){// case 2: there is either a path from S to T, or a path from T to S
			int ans=solve2();
			printf("%lld\n",ans);
		}else{// case 3: no path from S to T or from T to S 
			int ans=(poW(m,k-1)*(cnt-2)+(n-2)*(poW(m,k-1)-1)%mod*poW(m-1,mod-2)%mod+2)%mod;
			printf("%lld\n",ans);
		}
	}
	for(int i=1;i<=n;++i) ig[i].clear(),vc[i].clear(),belong[i]=dfn[i]=low[i]=stk[i]=head[i]=instk[i]=vis[i]=vis1[i]=vis2[i]=0;
	for(int i=1;i<=m;++i) to[i]=nxt[i]=0;

}
	return 0;
}