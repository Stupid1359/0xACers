#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef pair<int,int>P;
const int N=200005,M=1111111,inf=~0U>>1;
int Case,n,m,ca,cb,q,i,x,S,T,d[N],cov[N],f[N];
int pos[N*2],mia[M],mxb[M],best[M];
P pool[N*2];
vector<int>ga[N],gb[N];
struct E{int t,l,r,p;}a[N],b[N];
void build(int x,int a,int b){
  mia[x]=inf;
  mxb[x]=-1;
  best[x]=inf;
  if(a==b){
    pos[a]=x;
    return;
  }
  int mid=(a+b)>>1;
  build(x<<1,a,mid);
  build(x<<1|1,mid+1,b);
}
inline void change(int x,int a,int b){
  x=pos[x];
  mia[x]=a;
  mxb[x]=b;
  for(x>>=1;x;x>>=1){
    mia[x]=min(mia[x<<1],mia[x<<1|1]);
    mxb[x]=max(mxb[x<<1],mxb[x<<1|1]);
    best[x]=min(best[x<<1],best[x<<1|1]);
    if(mxb[x<<1]>=0&&mia[x<<1|1]<inf)best[x]=min(best[x],mia[x<<1|1]-mxb[x<<1]);
  }
}
inline int query(int S,int T){
  if(cov[S])return d[T]-d[S];
  if(f[S]==inf)return -1;
  return f[S]-d[n]+d[S]+d[T];
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>n>>ca>>cb>>q;
    for(i=1;i<=n;i++)cin>>d[i];
    for(i=1;i<=ca;i++){
      cin>>a[i].t>>a[i].l>>a[i].r;
      pool[i]=P(a[i].t-d[n]+2*d[a[i].r],i);
      cov[a[i].l]++;
      cov[a[i].r+1]--;
      ga[a[i].r].emplace_back(i);
    }
    for(i=1;i<=cb;i++){
      cin>>b[i].t>>b[i].l>>b[i].r;
      pool[i+ca]=P(b[i].t,-i);
      gb[b[i].l].emplace_back(i);
      gb[b[i].r+1].emplace_back(-i);
    }
    m=ca+cb;
    sort(pool+1,pool+m+1);
    for(i=1;i<=ca+cb;i++){
      x=pool[i].second;
      if(x>0)a[x].p=i;else b[-x].p=i;
    }
    build(1,1,m);
    for(i=1;i<=n;i++){
      for(const auto&it:ga[i])change(a[it].p,a[it].t,-1);
      for(const auto&it:gb[i])if(it>0)change(b[it].p,inf,b[it].t);else change(b[-it].p,inf,-1);
      cov[i]+=cov[i-1];
      f[i]=best[1];
    }
    while(q--){
      cin>>S>>T;
      cout<<query(S,T)<<"\n";
    }
    for(i=1;i<=n+1;i++){
      cov[i]=0;
      ga[i].clear();
      gb[i].clear();
    }
  }
}