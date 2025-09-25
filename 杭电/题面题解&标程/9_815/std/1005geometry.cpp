#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define db long double
#define mp make_pair
#define fo(i,l,r) for(ll i=l;i<=r;i++)
using namespace std;
const ll M=1e6+7;
const db Eps=1e-20;
ll n,x[M],y[M],cnt,X[M],Y[M],In[M],id[M]; db rd;
db ang(ll x1,ll y1,ll x2,ll y2){
	return atan2(x1*y2-x2*y1,x1*x2+y1*y2);
}
bool cmp(ll x,ll y){
	return X[x]<X[y] || (X[x]==X[y] && Y[x]<Y[y]);
}
int main(){
	// freopen("geometry.in","r",stdin);
	// freopen("geometry.out","w",stdout);
	int T; cin>>T; while(T--){
		scanf("%lld",&n),cnt=0,rd=0;
		fo(i,1,n) scanf("%lld%lld",&x[i],&y[i]);
		x[n+1]=x[1],y[n+1]=y[1];
		x[n+2]=x[2],y[n+2]=y[2];
		fo(i,1,n){
			rd+=ang(x[i+1]-x[i],y[i+1]-y[i],x[i+2]-x[i+1],y[i+2]-y[i+1]);
		}
		//rd 负：顺时针转；正：逆时针转
		fo(i,1,n){
			if(ang(x[i+1]-x[i],y[i+1]-y[i],x[i+2]-x[i+1],y[i+2]-y[i+1])>Eps) cnt++,X[cnt]=x[i+1],Y[cnt]=y[i+1],In[cnt]=1;
			if(ang(x[i+1]-x[i],y[i+1]-y[i],x[i+2]-x[i+1],y[i+2]-y[i+1])<-Eps) cnt++,X[cnt]=x[i+1],Y[cnt]=y[i+1],In[cnt]=0;
		}
		if(rd<0) for(int i=1;i<=cnt;i++) In[i]=1-In[i];
		for(int i=1;i<=cnt;i++) id[i]=i;
		sort(id+1,id+1+cnt,cmp);
		printf("%lld\n",cnt);
		for(int i=1;i<=cnt;i++){
			printf("%lld %lld ",X[id[i]],Y[id[i]]);
			if(In[id[i]]==1) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
