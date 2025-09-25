#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll pwr(ll x,ll y,ll m){
	ll res=1,cur=x;
	for(ll i=1;i<=y;i<<=1){
		if(i&y)res=res*cur%m;
		cur=cur*cur%m;
	}
	return res;
}
template<int M>
struct pl_mul{
	ll l,m,r;
	char tp;
	pl_mul(ll x=0){
		tp='N';
		r=x%M;
		l=m=0;
	}
	pl_mul(ll _l,ll _m,ll _r){
		l=_l%M; m=_m%M; r=_r%M;
		tp='C';
	}
	ll toll(){
		return (l+m+r)%M;
	}
};
template<int M>
pl_mul<M> operator + (pl_mul<M> a,pl_mul<M> b){
	if(a.tp=='N'){
		b.m+=b.l;
		if(b.m>=M)b.m-=M;
		return {a.r,b.m,b.r};
	}
	return {a.l,a.m+a.r+b.l+b.m,b.r};
}
template<int M>
pl_mul<M> operator * (pl_mul<M> a,pl_mul<M> b){
	if(a.tp=='N' && b.tp=='N')
		return {a.r * b.r};
	if(a.tp!='N' && b.tp=='N')
		return {a.l, a.m, a.r*b.r};
	if(a.tp=='N' && b.tp!='N')
		return {a.r*b.l, b.m, b.r};
	return {a.l, a.m+a.r*b.l+b.m, b.r};
}
const int Mod=1'000'000'007;
struct lsh{
	pl_mul<Mod> l;
	pl_mul<Mod-1> r,v;
	bool hasv;
	lsh(ll x=0){
		l=x; r=x; v=0;
		hasv=false;
	}
	lsh (pl_mul<Mod> _l,pl_mul<Mod-1> _r){
		l=_l; r=_r; v=0;
		hasv=false;
	}
	lsh(pl_mul<Mod> _l,pl_mul<Mod-1> _r,pl_mul<Mod-1> _v){
		l=_l; r=_r; v=_v;
		hasv=true;
	}
	ll toll(){
		return l.toll() * pwr(2,v.toll(),Mod) % Mod;
	}
	pl_mul<Mod-1> to_rht(){
		if(hasv)return r+v;
		return r;
	}
};
lsh operator + (lsh a, lsh b){
	if(a.hasv)
		return {a.l,a.r,a.v+b.to_rht()};
	if(b.hasv)
		return {a.l+b.l,a.r+b.r, b.v};
	return {a.l+b.l,a.r+b.r};
}
lsh operator * (lsh a,lsh b){
	if(a.hasv)
		return {a.l,a.r,a.v*b.to_rht()};
	if(b.hasv)
		return {a.l*b.l, a.r*b.r, b.v};
	return {a.l*b.l,a.r*b.r};
}
lsh operator << (lsh a,lsh b){
	if(a.hasv)
		return {a.l,a.r,a.v+b.to_rht()};
	return {a.l,a.r,b.to_rht()};
}
int n,a[300'005],b[300'005];
char tp[300'005];
lsh res[300'005];
bool vis[300'005];
lsh dfs(int x){
	if(vis[x])return res[x];
	vis[x]=true;
	if(tp[x]=='N')
		res[x]=a[x];
	else if(tp[x]=='<')
		res[x]=dfs(a[x]) << dfs(b[x]);
	else if(tp[x]=='+')
		res[x]=dfs(a[x]) + dfs(b[x]);
	else if(tp[x]=='*')
		res[x]=dfs(a[x]) * dfs(b[x]);
	return res[x];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",tp+i);
		if(tp[i]=='N')
			scanf("%d",&a[i]);
		else scanf("%d%d",&a[i],&b[i]);
	}
	for(int i=1;i<=n;i++)
		printf("%lld\n",dfs(i).toll());
	return 0;
}
