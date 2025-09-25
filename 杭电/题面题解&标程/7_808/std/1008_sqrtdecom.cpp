#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=50005,K=8,BLK=(N>>K)+1;
int Case,n,m,i,j;
vector<int>g[N];
ll ans;
int rangel[N],ranger[N],pool[N*2],cb,st[BLK],en[BLK];
int at[BLK][N],cov[BLK][(1<<(K+1))+5],val[BLK][(1<<(K+1))+5],sz[BLK],sum[BLK];
struct E{int u,l,r,L,R;}e[N];
inline bool cmp(const E&a,const E&b){return a.u<b.u;}
inline void init(){
  int i,j,k,cp,_;
  for(i=1,j=0;i<=n;i++){
    while(j<m&&e[j+1].u<=i)j++;
    ranger[i]=j;
  }
  for(i=n,j=m+1;i;i--){
    while(j>1&&e[j-1].u>=i)j--;
    rangel[i]=j;
  }
  cb=m>>K;
  for(i=1;i<=m;i++)en[i>>K]=i;
  for(i=m;i;i--)st[i>>K]=i;
  pool[0]=0;
  for(i=0;i<=cb;i++){
    sum[i]=0;
    pool[cp=1]=n;
    for(j=st[i];j<=en[i];j++){
      pool[++cp]=e[j].l-1;
      pool[++cp]=e[j].r;
    }
    sort(pool,pool+cp+1);
    _=cp;
    cp=0;
    for(j=1;j<=_;j++)if(pool[j]>pool[j-1])pool[++cp]=pool[j];
    sz[i]=cp;
    for(j=0;j<=cp;j++)cov[i][j]=val[i][j]=0;
    for(j=1;j<=cp;j++)for(k=pool[j-1]+1;k<=pool[j];k++)at[i][k]=j;
    for(j=st[i];j<=en[i];j++){
      e[j].L=at[i][e[j].l];
      e[j].R=at[i][e[j].r];
      cov[i][e[j].L]++;
      cov[i][e[j].R+1]--;
    }
    for(j=1;j<=cp;j++)cov[i][j]+=cov[i][j-1];
  }
}
inline void modify(int x,int p){
  for(int i=0;i<=cb;i++){
    int y=at[i][x];
    sum[i]+=cov[i][y]*p;
    val[i][y]+=p;
  }
}
inline void ask(int o,int l,int r){
  int i,m=sz[o];
  for(i=1;i<=m;i++)pool[i]=pool[i-1]+val[o][i];
  for(i=l;i<=r;i++)ans+=pool[e[i].R]-pool[e[i].L-1];
}
inline void query(int l,int r){
  l=rangel[l],r=ranger[r];
  if(l>r)return;
  int L=l>>K,R=r>>K;
  for(int i=L+1;i<R;i++)ans+=sum[i];
  if(L==R)ask(L,l,r);
  else{
    ask(L,l,en[L]);
    ask(R,st[R],r);
  }
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>n>>m;
    ans=0;
    for(i=1;i<=n+1;i++)g[i].clear();
    for(i=1;i<=m;i++)cin>>e[i].u>>e[i].l>>e[i].r;
    sort(e+1,e+m+1,cmp);
    for(i=1;i<=m;i++){
      g[e[i].l].emplace_back(i);
      g[e[i].r+1].emplace_back(-i);
    }
    init();
    for(i=1;i<=n;i++){
      for(const auto&it:g[i])if(it>0)modify(e[it].u,1);else modify(e[-it].u,-1);
      for(j=rangel[i];j<=ranger[i];j++)query(e[j].l,e[j].r);
    }
    cout<<ans<<"\n";
  }
}