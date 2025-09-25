#include<bits/stdc++.h>
using namespace std;
using us=unsigned short;
int read(){
	int x=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
const int B=16,N=2'000'005;
struct base{
	us b[B];
	base(){memset(b,0,sizeof b);}
	base(us x){
		memset(b,0,sizeof b);
		if(x)b[__lg(x)]=x;
	}
	int query(int x){
		for(int i=B-1;i>=0;i--){
			if((x&(1<<i))==0)
				x^=b[i];
		}
		return x;
	}
};
void operator += (base &p,auto &q){
	for(int i=0;i<B;i++){
		us x=q.b[i];
		if(x==0)continue;
		for(int j=i;j>=0;j--)
			if(x&(1<<j)){
				if(p.b[j])x^=p.b[j];
				else{
					p.b[j]=x;
					break;
				}
			}
	}
}
struct base_t{
	us b[B]; int t[B];
	base_t(){memset(b,0,sizeof b);memset(t,0,sizeof t);}
	void append(int x,int tme){
		if(x==0)return;
		for(int i=B-1;i>=0;i--)
			if(x&(1<<i)){
				if(b[i]){
					if(t[i]<tme){
						int y=b[i]^x,ty=t[i];
						b[i]=x; t[i]=tme;
						x=y; tme=ty;
					}
					else
						x^=b[i];
				}
				else{
					b[i]=x;
					t[i]=tme;
					return;
				}
			}
	}
	base extract(int tme){
		base res;
		for(int i=0;i<B;i++)
			if(t[i]>=tme)
				res.b[i]=b[i];
		return res;
	}
};
int n,m,q,val[N],fa[N],rng[N];
struct edge{int to,dis;};
vector<edge> g[N];
vector<int> tr[N];
void delring(int u,int frm){
	fa[u]=frm;
	for(edge v:g[u]){
		if(v.to==frm)continue;
		if(fa[v.to]){
			if(fa[fa[v.to]]==u)continue;
			n++;
			rng[n]=val[v.to]^val[u]^v.dis;
			fa[n]=v.to;
			for(int i=u;i!=v.to;){
				int j=fa[i];
				fa[i]=n;
				i=j;
			}
			continue;
		}
		val[v.to]=val[u]^v.dis;
		delring(v.to,u);
	}
}
int sz[N],h[N],tp[N];
base_t bs[N];
void scan(int u){
	sz[u]=1;
	for(int i:tr[u]){
		h[i]=h[u]+1;
		scan(i);
		sz[u]+=sz[i];
	}
}
void decomp(int u,int top){
	tp[u]=top;
	if(top!=u)
		bs[u]=bs[fa[u]];
	bs[u].append(rng[u],h[u]);
	if(tr[u].size()==0)return;
	int best=0;
	for(int i:tr[u])
		if(sz[i]>sz[best])best=i;
	decomp(best,top);
	for(int i:tr[u]){
		if(i!=best)
			decomp(i,i);
	}
}
int query(int x,int y){
	int init=val[x]^val[y];
	base cur;
	while(tp[x]!=tp[y]){
		if(h[tp[x]]>=h[tp[y]]){
			cur+=bs[x];
			x=fa[tp[x]];
		}
		else{
			cur+=bs[y];
			y=fa[tp[y]];
		}
	}
	if(h[x]>h[y])swap(x,y);
	base last=bs[y].extract(h[x]);
	cur+=last;
	return cur.query(init);
}
int main(){
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		g[u].emplace_back((edge){v,w});
		g[v].emplace_back((edge){u,w});
	}
	delring(1,1);
	for(int i=2;i<=n;i++)
		tr[fa[i]].emplace_back(i);
	scan(1);
	decomp(1,N-2);
	for(;q;q--){
		int x,y;
		x=read();y=read();
		printf("%d\n",query(x,y));
	}
	return 0;
}
