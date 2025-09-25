#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define wt int tt=d;while(tt--)
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d rd()
struct node{ll u,v,w,c,nx;}e[1000010];
ll hd[100010],cnt=1;
void add(ll u,ll v,ll w,ll c){e[++cnt]={u,v,w,c,hd[u]};hd[u]=cnt;}
void ad(ll u,ll v,ll w,ll c){add(u,v,w,c),add(v,u,0,-c);}
ll n,m,S,T,nodes;
ll cst;
ll pre[100010];
ll dis[100010];
#define inf 0x3f3f3f3f
ll arg(){
	ll u,v=T,fl=inf;
	while(v!=S)u=pre[v],fl=min(fl,e[u].w),v=e[u].u;
	v=T;while(v!=S)u=pre[v],e[u].w-=fl,e[u^1].w+=fl,v=e[u].u;
	cst+=fl*dis[T];return fl;
}
queue<ll>q;
bool in[100010];
bool spfa(){
	while(!q.empty())q.pop();
	f(i,1,nodes)dis[i]=inf,pre[i]=in[i]=0;dis[S]=0;q.push(S);in[S]=1;
	while(!q.empty()){
		ll u=q.front();q.pop();in[u]=0;
		for(int i=hd[u];i;i=e[i].nx){
			if(e[i].w==0)continue;ll v=e[i].v;
			if(dis[u]+e[i].c<dis[v]){
				dis[v]=dis[u]+e[i].c;pre[v]=i;
				if(!in[v])in[v]=1,q.push(v);
			}
		}
	}return dis[T]!=inf;
}
ll s[210][210],a[210][210],k;
ll id(ll i,ll j){
	return (i-1)*m+j;
}
ll b[210][210];
ll deg[100010];
ll res;
void solve(){
	n=d,m=d;k=d;cnt=1;cst=0;res=0;
	f(i,1,nodes)hd[i]=deg[i]=0;
	f(i,1,n)f(j,1,m)s[i][j]=d;
	f(i,1,n)f(j,1,m)a[i][j]=d;
	if(n==1){
		f(i,1,m)if(s[1][i]!=s[1][1]){puts("Impossible");return;}
		puts("0");return;
	}if(m==1){
		f(i,1,n)if(s[i][1]!=s[1][1]){puts("Impossible");return;}
		puts("0");return;
	}
	f(i,1,n)f(j,1,m)s[i][j]=(k-s[i][j])%k;
	ll X=(s[1][1]-s[1][2]-s[2][1]+2*k)%k;
	f(i,1,n)f(j,1,m)s[i][j]=(s[i][j]+X)%k,b[i][j]=0;
	res+=s[1][1]*a[1][1];b[1][1]=s[1][1];
	f(j,1,m-1){
		ad(id(1,j),id(1,j+1),inf,a[1][j+1]);
		b[1][j]-=s[1][j+1];
		b[1][j+1]+=s[1][j+1];
		res+=s[1][j+1]*a[1][j+1];
	}
	f(i,2,n){
		f(j,1,m){
			ad(id(i-1,j),id(i,j),inf,a[i][j]);
			ll x=(b[i-1][j]%k+k)%k;
			b[i-1][j]-=x,b[i][j]+=x;
			res+=x*a[i][j];
		}
		if(b[i][1]!=s[i][1]){puts("Impossible");return;}
		f(j,1,m-1){
			ad(id(i,j),id(i,j+1),inf,a[i][j+1]);
			ll x=(s[i][j+1]-b[i][j+1]%k+k)%k;
			b[i][j]-=x;b[i][j+1]+=x;
			res+=x*a[i][j+1];
		}
	}
	b[n][m]-=s[n][m];
	ll SS=n*m+1,TT=n*m+2;
	if(b[n][m]%k!=0){puts("Impossible");return;}
	ad(SS,id(1,1),inf,a[1][1]);
	ad(id(n,m),TT,inf,0);
	ad(TT,SS,inf,0);
	f(i,1,n)f(j,1,m)if(b[i][j]!=0){
		b[i][j]/=k;
		if(b[i][j]<0)deg[id(i,j)]-=-b[i][j],deg[TT]+=-b[i][j];
		else deg[id(i,j)]+=b[i][j],deg[SS]-=b[i][j];
	}
	S=TT+1,T=nodes=S+1;
	ll x=0;
	f(i,1,n*m+2)if(deg[i]!=0){
		if(deg[i]>0)ad(S,i,deg[i],0),x+=deg[i];
		if(deg[i]<0)ad(i,T,-deg[i],0);
	}
	ll fl=0;
	while(spfa())fl+=arg();
	if(fl!=x){puts("Impossible");return;}
	res+=k*cst;
	cout<<res<<endl;
}
int main(){
	wt solve();
	return 0;
}

