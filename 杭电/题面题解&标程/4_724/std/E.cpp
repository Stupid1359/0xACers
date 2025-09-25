#include<bits/stdc++.h>
using namespace std;
 
const int mxn=5e5+5;
int opt[mxn],n,q,root=1;
int nw[mxn];
vector<int>g[mxn];
 
int ccnt,bg[mxn],ed[mxn];
int top[mxn],sz[mxn],dep[mxn],ord[mxn];
int fa[mxn];
int a[mxn];
inline void pre_dfs(int x,int par=0,int deep=1){
	sz[x]=1;dep[x]=deep;fa[x]=par;
	for(int y:g[x])if(y!=par)pre_dfs(y,x,deep+1),sz[x]+=sz[y];
}
inline void go(int x,int tpf=root,int par=0){
	bg[x]=++ccnt;ord[ccnt]=x,top[x]=tpf;
	int mx=-1,pos=0;
	for(int y:g[x])if(y!=par){
		if(sz[y]>mx){
			mx=sz[y];
			pos=y;
		}
	}
	if(mx==-1)goto eed;
	go(pos,tpf,x);
	for(int y:g[x])if(y!=par and y!=pos)go(y,y,x);
	eed:;
	ed[x]=ccnt;
}
struct segt{
	int val[mxn*8];
	void init(){}
	void build(int x,int l,int r){
		if(l==r){
			val[x]=(bool)(a[ord[l]]>1);
			return;
		}
		int md=l+r>>1;
		build(x<<1,l,md);
		build(x<<1|1,md+1,r);
		val[x]=val[x<<1]|val[x<<1|1];
	}
	void modify(int x,int l,int r,int c,int d){
		if(l==r){
			val[x]=d;
			return;
		}
		int md=l+r>>1;
		if(c<=md)modify(x<<1,l,md,c,d);
		else modify(x<<1|1,md+1,r,c,d);
		val[x]=val[x<<1]|val[x<<1|1];
	}
	int find(int x,int l,int r){
		if(l==r)return ord[l];
		int md=l+r>>1;
		if(val[x<<1|1])return find(x<<1|1,md+1,r);
		else return find(x<<1,l,md);
	}
	int calc(int x,int l,int r,int a,int b){
		if(r<a or b<l)return -1;
		if(val[x]==0)return -1;
		if(a<=l and r<=b)return find(x,l,r);
		int md=l+r>>1;
		int t=calc(x<<1|1,md+1,r,a,b);
		if(t>=1)return t;
		return calc(x<<1,l,md,a,b);
	}
}sgt;
int lca(int x,int y){
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])x=fa[top[x]];
		else y=fa[top[y]];
	} 
	return dep[x]>dep[y]?y:x;
}
int lst(int x){
	for(;top[x]!=1;){
		int t=sgt.calc(1,1,n,bg[top[x]],bg[x]);
		if(t>=1)return t;
		x=top[x],x=fa[x];
	}
	int t=sgt.calc(1,1,n,1,bg[x]);
	if(t>=1)return t;
	return 0;
}
int vl[mxn],vr[mxn];
#define ll int 
inline ll read() {
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-') f=-f;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void write(ll x) {
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar(x%10+'0');
}
inline void solve(){
	n=read(),q=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1,u,v;i<n;++i){
		u=read(),v=read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	pre_dfs(1);go(1);
	sgt.build(1,1,n);
//	for(int i=1;i<=n;++i)cerr<<lst(i)<<' ';cerr<<'\n';
	for(;q--;){
		int op,l,r;op=read(),l=read(),r=read();
		if(op==1){
			int sl=0,sr=0;
			int cnt=0,dp=0;
			int zx=lca(l,r);
			while(dep[l]>=dep[zx] and a[l]>1){
				vl[sl++]=a[l];
				l=fa[l];
				++cnt;
				if(cnt>12){
					write(0),putchar('\n');
					goto ed;
				}
			}
			while(dep[l]>=dep[zx]){//include zx
				int lt=lst(l);
				if(dep[lt]>=dep[zx]){
					for(int i=0;i<min(24,dep[l]-dep[lt]);++i)vl[sl++]=1;
					vl[sl++]=a[lt];
					l=lt;l=fa[l];
					++cnt;
				}else{
					for(int i=0;i<min(24,dep[l]-dep[zx]);++i)vl[sl++]=1;
					vl[sl++]=a[zx];
					break;
				}
				if(cnt>12){
					write(0),putchar('\n');
					goto ed;
				}
			}
			while(dep[r]>dep[zx] and a[r]>1){
				vr[sr++]=a[r];
				r=fa[r];
				++cnt;
				if(cnt>12){
					write(0),putchar('\n');
					goto ed;
				}
			}
			while(dep[r]>dep[zx]){
				int lt=lst(r);
				if(dep[lt]>dep[zx]){
					for(int i=0;i<min(24,dep[r]-dep[lt]);++i)vr[sr++]=1;
					vr[sr++]=a[lt];
					r=lt;r=fa[r];
					++cnt;
				}else{
					for(int i=0;i<min(24,dep[r]-dep[zx]);++i)vr[sr++]=1;
					break;
				}
				if(cnt>12){
					write(0),putchar('\n');
					goto ed;
				}
			}
			for(int i=sr-1;~i;--i)vl[sl++]=vr[i];
			for(int i=0;i<sl;++i)if(vl[i]>24){
				write(0),putchar('\n');
				goto ed;
			}
			dp|=(1<<vl[0]);
			for(int i=1;i<sl;++i){
				if(vl[i]==1){
					dp|=(dp<<1);
					if(dp&(1<<25))dp-=(1<<25);
				}else{
					int tdp=0;
					for(int j=1;j<=24;++j){
						if(dp&(1<<j)){
							if(j*vl[i]<=24)tdp|=(1<<(j*vl[i]));
							if(j+vl[i]<=24)tdp|=(1<<(j+vl[i]));
						}
					}
					dp=tdp;
				}
			}
			if(dp&(1<<24))write(1),putchar('\n');
			else write(0),putchar('\n');
			ed:;
		}else{
			int x=l,d=r;
			sgt.modify(1,1,n,bg[x],(bool)(d>1));
			a[x]=d;
		}
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;
	for(;T--;)solve();
	return 0;
}