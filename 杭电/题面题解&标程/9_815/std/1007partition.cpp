#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int Mod=998244353,N=500005;
struct dpnode{
	ll f,g;
	ll d(){return f-g;}
}src[N];
dpnode operator + (dpnode x,dpnode y){
	return {(x.f*y.f+x.g*y.f+x.f*y.g)%Mod, (x.f*y.g+x.g*y.f)%Mod};
}
vector<dpnode> dp[N];
struct edge{int to,eid;};
vector<edge> g[N],ig[N];
int n,ans[N];
int main(){
	scanf("%d",&n);
	ig[n].emplace_back((edge){1,0});
	for(int i=1;i<n;i++)
		ig[i+1].emplace_back((edge){i,0});
	for(int i=1;i<=n-3;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		if(u<v)swap(u,v);
		ig[u].emplace_back((edge){v,i});
	}
	for(int i=1;i<=n;i++)
		for(edge j:ig[i])
			g[j.to].emplace_back((edge){i,j.eid});
	for(int x=n-1;x>0;x--){
		dp[x].emplace_back((dpnode){1,1});
		for(int j=1;j<g[x].size();j++)
			dp[x].emplace_back(dp[x].back()+dp[g[x][j-1].to].back());
	}
	src[1]={1,1};
	for(int x=1;x<n;x++){
		dpnode cur=src[x];
		for(int j=g[x].size()-1;j>0;j--){
			ans[g[x][j].eid]=(cur.g*dp[x][j].d() + cur.d()*dp[x][j].g)%Mod;
			int y=g[x][j-1].to;
			src[y]=dp[x][j-1] + cur;
			cur=cur+dp[y].back();
		}
	}
	for(int i=1;i<=n-3;i++)
		printf("%d\n",(ans[i]+Mod)%Mod);
	return 0;
}
