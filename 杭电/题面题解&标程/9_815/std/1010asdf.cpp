#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}
const ll N=500010,M=3000010;
#define pb push_back
ll Tst,n,a[N],dfn[N],low[N],st[N],s[N],ins[N],c[N],b[N],ss[N],num,t,cnt,ans,f[N],deg[N];
vector<ll> A[N],e[N];ll ver[M],nxt[M],head[N],tot;
void add(ll x,ll y){ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;}
void Tarjan(ll x){
	dfn[x]=low[x]=++num,ins[x]=1,st[++t]=x;
	for(ll i=head[x];i;i=nxt[i]){
		ll y=ver[i];
		if(!dfn[y])Tarjan(y),low[x]=min(low[x],low[y]);
		else if(ins[y])low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		ll y;cnt++;
		do{y=st[t--],ins[y]=0,c[y]=cnt,s[cnt]+=a[y]>0,ss[cnt]++;}while(y^x);
	}
}
queue<ll> Q;
void Top(){
	for(ll i=1;i<=cnt;i++)if(!deg[i])Q.push(i);
	while(Q.size()){
		ll x=Q.front();Q.pop();
		if(ss[x]>1&&s[x])f[x]=1;
		for(auto y:e[x]){f[y]|=f[x],s[y]+=s[x];if(!(--deg[y]))Q.push(y);}
	}
}
map<ll,ll> bbb[N];
void work(){
	n=read(),tot=num=cnt=t=ans=0;
	memset(head,0,sizeof(head)),memset(f,0,sizeof(f));
	memset(dfn,0,sizeof(dfn)),memset(low,0,sizeof(low));
	memset(deg,0,sizeof(deg)),memset(ins,0,sizeof(ins));
	memset(s,0,sizeof(s)),memset(ss,0,sizeof(ss));
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=n;i++)b[i]=read();
	for(ll i=1;i<=n;i++)for(ll j=1,x;j<=b[i];j++)x=read(),A[i].pb(x),assert(bbb[i][x]==0);
	for(ll i=1;i<=n;i++)for(ll j=0;j<b[i];j++)add(i,A[i][j]);
	for(ll i=1;i<=n;i++)if(!dfn[i])Tarjan(i);
	for(ll x=1;x<=n;x++)
		for(ll i=head[x];i;i=nxt[i])
			if(c[ver[i]]^c[x])e[c[x]].pb(c[ver[i]]),deg[c[ver[i]]]++;
	Top();
	for(ll i=1;i<=cnt;i++)ans+=!f[i]*ss[i];
	printf("%lld\n",n-ans);
	for(ll i=1;i<=n;i++)A[i].clear(),A[i].shrink_to_fit(),bbb[i].clear();
	for(ll i=1;i<=cnt;i++)e[i].clear(),e[i].shrink_to_fit();
}
int main(){
	Tst=read();while(Tst--)work();
	return 0;
}
