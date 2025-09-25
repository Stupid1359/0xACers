#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
bool st;
const int N=80009;
char buf[1<<22],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<22,stdin),p1==p2)?EOF:*p1++)
inline int read(){
	int x=0;char ch=0;
	while((ch<'0'||ch>'9'))ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch-'0'),ch=getchar();
	return x;
}
inline void write(int x,char tl=0){
	static int sta[10];
	int top=0;
	do{sta[top++]=x%10,x/=10;}while(x);
	while(top)putchar(sta[--top]+48);
	if(tl)putchar(tl);
}
int n,q,R,lans;
vector<int> g[N];
int fa[N],son[N],dn[N],tp[N],sz[N],dep[N],dfn[N],dfnc,dfa[N],lsz[N];
void dfs1(int u,int f){
	fa[u]=f;sz[u]=1;dep[u]=dep[f]+1;
	for(int v:g[u])if(v!=f){
		dfs1(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]])son[u]=v;
	}
	lsz[u]=sz[u]-sz[son[u]];
}
void dfs2(int u,int up){
	dn[up]=u;tp[u]=up;
	dfa[dfn[u]=++dfnc]=u;
	if(son[u])dfs2(son[u],up);
	for(int v:g[u])if(v!=fa[u]&&v!=son[u])dfs2(v,v);
}
array<int,2> nod[N];int ctop;
void gnod(int u,int forb,int x){
	nod[++ctop]={u,x};
	for(int v:g[u])if(v!=forb)gnod(v,forb,x);
}
int rt[N];
struct segtree{
	struct Node1{
		int mid,ls,rs;
		void clear(){ls=rs=mid=0;}
	}tr1[N<<1];int top1=0;
	int mx2[13000000];
	int b2[5000000],cut2[N<<1],pre2[N<<1];
	int mx3[7000000];
	int b3[2500000],cut3[N<<1],pre3[N<<1];
	void init(){
		for(int i=0;i<=pre2[top1];i++)mx2[i]=0;
		for(int i=0;i<=pre3[top1];i++)mx3[i]=0;
		for(int i=0;i<=top1;i++)tr1[i].clear(),cut2[i]=cut3[i]=0;
		top1=0;
		for(int i=0;i<=n;i++)rt[i]=0;
	}
	int gmx(int l,int r,int x=1){
		if(l==r)return x;
		return max(gmx(l,l+r>>1,x<<1),gmx((l+r>>1)+1,r,x<<1|1));
	}
	void upd2(int xl,int xr,int x,int l,int r,int p,int ad){
		if(xl>xr)return ;
		if(xl<=l&&r<=xr)return mx2[p+ad]=max(mx2[p+ad],x),void();
		int mid=l+r>>1;
		if(xl<=mid)upd2(xl,xr,x,l,mid,p<<1,ad);
		if(xr>mid)upd2(xl,xr,x,mid+1,r,p<<1|1,ad);
	}
	int qmx2(int xp,int l,int r,int p,int ad){
		int x=mx2[p+ad];
		if(l==r)return x;
		int mid=l+r>>1;
		if(xp<=mid)return max(x,qmx2(xp,l,mid,p<<1,ad));
		else return max(x,qmx2(xp,mid+1,r,p<<1|1,ad));
	}
	void upd3(int xp,int x,int l,int r,int p,int ad){
		mx3[p+ad]=max(mx3[p+ad],x);
		if(l==r)return ;
		int mid=l+r>>1;
		if(xp<=mid)upd3(xp,x,l,mid,p<<1,ad);
		else upd3(xp,x,mid+1,r,p<<1|1,ad);
	}
	int qmx3(int k,int x,int l,int r,int p,int ad){
		if(k>=r&&mx3[p+ad]<x)return l-1;
		if(l==r)return l;
		int mid=l+r>>1;
		if(k<=mid)return qmx3(k,x,l,mid,p<<1,ad);
		int y=qmx3(k,x,mid+1,r,p<<1|1,ad);
		if(y>mid)return y;
		return qmx3(k,x,l,mid,p<<1,ad);
	}
	int build(int l,int r,int sum){
		int p=++top1;ctop=0;
		for(int i=l;i<=r;i++)gnod(dfa[i],son[dfa[i]],dep[dfa[i]]);
		cut2[p]=cut2[p-1];cut3[p]=cut3[p-1];
		b2[++cut2[p]]=-n;b3[++cut3[p]]=-n;
		for(int i=1;i<=ctop;i++){
			auto u=nod[i];
			b2[++cut2[p]]=u[0]-u[1],b2[++cut2[p]]=u[0]+1,b3[++cut3[p]]=u[0]+u[1];
		}
		sort(b2+cut2[p-1]+1,b2+cut2[p]+1);
		sort(b3+cut3[p-1]+1,b3+cut3[p]+1);
		cut2[p]=unique(b2+cut2[p-1]+1,b2+cut2[p]+1)-b2-1;
		cut3[p]=unique(b3+cut3[p-1]+1,b3+cut3[p]+1)-b3-1;
		pre2[p]=pre2[p-1]+gmx(cut2[p-1]+1,cut2[p]);
		pre3[p]=pre3[p-1]+gmx(cut3[p-1]+1,cut3[p]); 
		for(int i=1;i<=ctop;i++){
			auto u=nod[i];
			int xl=lower_bound(b2+cut2[p-1]+1,b2+cut2[p]+1,u[0]-u[1])-b2;
			int xr=lower_bound(b2+cut2[p-1]+1,b2+cut2[p]+1,u[0]+1)-b2-1;
			upd2(xl,xr,u[0]+u[1],cut2[p-1]+1,cut2[p],1,pre2[p-1]);
			int xp=lower_bound(b3+cut3[p-1]+1,b3+cut3[p]+1,u[0]+u[1])-b3;
			upd3(xp,u[0],cut3[p-1]+1,cut3[p],1,pre3[p-1]);
		}
		if(l==r)return p;
		array<int,3> mn={sum,0,0};
		for(int i=l,psum=0;i<=r;i++){
			psum+=lsz[dfa[i]];
			mn=min(mn,array<int,3>{max(psum,sum-psum),i,psum});
			if(psum>=sum-psum)break;
		}
		tr1[p].mid=mn[1];
//		tr1[p].mid=(l+r>>1);
		tr1[p].ls=build(l,tr1[p].mid,mn[2]);
		tr1[p].rs=build(tr1[p].mid+1,r,sum-mn[2]);
		return p;
	}
	int qry2(int xl,int xr,int x,int l,int r,int p){
		if(xl>xr)return 0;
		if(xl<=l&&r<=xr)return qmx2(upper_bound(b2+cut2[p-1]+1,b2+cut2[p]+1,x)-b2-1,cut2[p-1]+1,cut2[p],1,pre2[p-1]);
		int res=0;
		if(xl<=tr1[p].mid)res=max(res,qry2(xl,xr,x,l,tr1[p].mid,tr1[p].ls));
		if(xr>tr1[p].mid)res=max(res,qry2(xl,xr,x,tr1[p].mid+1,r,tr1[p].rs));
		return res;
	}
	int qry3(int xl,int xr,int x,int y,int l,int r,int p){
		if(xl>xr)return 0;
		if(xl<=l&&r<=xr){
			int s=qmx3(upper_bound(b3+cut3[p-1]+1,b3+cut3[p]+1,x)-b3-1,y,cut3[p-1]+1,cut3[p],1,pre3[p-1]);
			if(s>cut3[p-1])return b3[s];
			else return 0;
		}
		int res=0;
		if(xl<=tr1[p].mid)res=max(res,qry3(xl,xr,x,y,l,tr1[p].mid,tr1[p].ls));
		if(xr>tr1[p].mid)res=max(res,qry3(xl,xr,x,y,tr1[p].mid+1,r,tr1[p].rs));
		return res;
	}
}tr;
int rt2[N];
struct segtree2{
	struct Node{
		int ls,rs,sum;
		void clear(){ls=rs=sum=0;}
	}tr[1600000];int top;
	void init(){
		for(int i=1;i<=n;i++)rt2[i]=0;
		for(int i=0;i<=top;i++)tr[i].clear();
		top=0;
	}
	int insert(int x,int l,int r,int rt){
		int p=++top;
		tr[p]=tr[rt];tr[p].sum++;
		if(l==r)return p;
		int mid=l+r>>1;
		if(x<=mid)tr[p].ls=insert(x,l,mid,tr[p].ls);
		else tr[p].rs=insert(x,mid+1,r,tr[p].rs);
		return p;
	}
	int query(int u,int v,int k,int l,int r){
		if(tr[v].sum-tr[u].sum==0)return l-1;
		if(l==r)return l;
		int mid=l+r>>1;
		if(k<=mid)return query(tr[u].ls,tr[v].ls,k,l,mid);
		int p=query(tr[u].rs,tr[v].rs,k,mid+1,r);
		if(p>mid)return p;
		return query(tr[u].ls,tr[v].ls,k,l,mid);
	}
	int qry(int xl,int xr,int x,int y){
		x=max(x,1);
		if(xl>xr||x>y)return -n;
		int f=query(rt2[xl-1],rt2[xr],y,1,n);
		if(f>=x)return f;
		return -n;
	}
}tr2;
bool ed;
signed main(){
//	freopen("input.in","r",stdin);
//	freopen("std.out","w",stdout);
//	cerr<<(&st-&ed)/1024.0/1024.0<<endl;
	int cas=read();
	while(cas--){
		n=read();q=read();R=lans=0;
		for(int i=1;i<=n;i++)son[i]=dn[i]=tp[i]=sz[i]=dep[i]=dfn[i]=dfnc=dfa[i]=lsz[i]=0,g[i].clear();
		for(int i=1;i<=n;i++)g[fa[i]=read()].push_back(i),R+=(!fa[i])*i;
		dfs1(R,0);dfs2(R,R);
		tr.init();tr2.init();
		for(int i=1;i<=n;i++)if(i==tp[i])rt[i]=tr.build(dfn[i],dfn[dn[i]],sz[i]);
		for(int i=1;i<=n;i++)rt2[i]=tr2.insert(dfa[i],1,n,rt2[i-1]);
//		cerr<<tr.cut2[tr.top1]<<' '<<tr.cut3[tr.top1]<<' '<<tr.pre2[tr.top1]<<' '<<tr.pre3[tr.top1]<<' '<<tr2.top<<endl;
		while(q--){
			int u=read(),y=read(),z=read();
			u=(u+lans)%n+1;
			y=(y+lans)%(2*n-1)-(n-1);
			z=(z+lans)%(2*n-1)+1;
			lans=0;
			int w=(z-y)/2,fb=0;
			while(u){
				int v=tp[u];
				lans=max(lans,tr.qry2(dfn[v],min(dfn[u]-1,dfn[v]+w-dep[v]),y,dfn[v],dfn[dn[v]],rt[v]));
				lans=max(lans,tr.qry3(max(dfn[v],dfn[v]+w+1-dep[v]),dfn[u]-1,z,y,dfn[v],dfn[dn[v]],rt[v]));
				if(!fb)lans=max(lans,tr2.qry(dfn[u],dfn[u]+sz[u]-1,y,min(y+dep[u],z-dep[u]))+dep[u]);
				else{
					lans=max(lans,tr2.qry(dfn[u],dfn[fb]-1,y,min(y+dep[u],z-dep[u]))+dep[u]);
					lans=max(lans,tr2.qry(dfn[fb]+sz[fb],dfn[u]+sz[u]-1,y,min(y+dep[u],z-dep[u]))+dep[u]);
				}
				fb=v;u=fa[v];
			} 
			write(lans,'\n');
		}
	}
	return 0;
}
