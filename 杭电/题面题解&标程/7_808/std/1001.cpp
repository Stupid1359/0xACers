#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
typedef pair<int,int>P;
const int N=10005,inf=1000000000;
int Case,n,s,w,h,i,x,y,z,ans,lim,at[N],st[N],en[N],val[N],mx[N],tag[N];
vector<P>f[N],g[N];
inline void up(int&a,int b){a<b?(a=b):0;}
inline void add(int l,int r,int p){
  int L=at[l],R=at[r],i,nmx;
  if(L==R){
    nmx=mx[L];
    for(i=l;i<=r;i++){
      val[i]+=p;
      up(nmx,val[i]);
    }
    mx[L]=nmx;
    up(ans,nmx+tag[L]);
    return;
  }
  nmx=mx[L];
  for(i=l;i<=en[L];i++){
    val[i]+=p;
    up(nmx,val[i]);
  }
  mx[L]=nmx;
  up(ans,nmx+tag[L]);
  
  nmx=mx[R];
  for(i=st[R];i<=r;i++){
    val[i]+=p;
    up(nmx,val[i]);
  }
  mx[R]=nmx;
  up(ans,nmx+tag[R]);
  
  for(i=L+1;i<R;i++){
    tag[i]+=p;
    up(ans,mx[i]+tag[i]);
  }
}
inline void del(int l,int r,int p){
  int L=at[l],R=at[r],i,nmx;
  if(L==R){
    for(i=l;i<=r;i++)val[i]-=p;
    nmx=-inf;
    for(i=st[L];i<=en[L];i++)up(nmx,val[i]);
    mx[L]=nmx;
    return;
  }
  for(i=l;i<=en[L];i++)val[i]-=p;
  nmx=-inf;
  for(i=st[L];i<=en[L];i++)up(nmx,val[i]);
  mx[L]=nmx;
  
  for(i=st[R];i<=r;i++)val[i]-=p;
  nmx=-inf;
  for(i=st[R];i<=en[R];i++)up(nmx,val[i]);
  mx[R]=nmx;
  
  for(i=L+1;i<R;i++)tag[i]-=p;
}
inline void gao(int w,int h,vector<P>f[]){
  int i;
  lim=sqrt(h);
  lim=max(lim,1);
  for(i=1;i<=n;i++){
    at[i]=(i-1)/lim;
    en[at[i]]=i;
    val[i]=0;
  }
  for(i=0;i<=at[n];i++)tag[i]=mx[i]=0;
  for(i=n;i;i--)st[at[i]]=i;
  for(i=1;i<=n;i++){
    if(i>w)
      for(const auto&it:f[i-w])
        del(it.first,min(it.first+h-1,n),it.second);
    for(const auto&it:f[i])
      add(it.first,min(it.first+h-1,n),it.second);
  }
}
inline void solve(int w,int h){
  if(w>h)gao(w,h,f);
  else gao(h,w,g);
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>n>>s;
    for(i=1;i<=n;i++)f[i].clear(),g[i].clear();
    for(i=1;i<=n;i++){
      cin>>x>>y>>z;
      f[x].emplace_back(P(y,z));
      g[y].emplace_back(P(x,z));
    }
    ans=0;
    for(w=1;w<=n&&w<=s;w++){
      h=min(s/w,n);
      w=min(s/h,n);
      solve(w,h);
    }
    cout<<ans<<"\n";
  }
}